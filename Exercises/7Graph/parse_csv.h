#ifndef GRAPH_PARSE_CSV_H
#define GRAPH_PARSE_CSV_H

#include <string>       //std::string
#include <fstream>
#include "graph.h"

#include <typeinfo>
class csvReader
{
public:
    csvReader(std::string filename)
        : filename_(filename)
    { }

    /*
    * Parses through csv file line by line and returns the data
    * in vector of vector of strings.
    */
    std::vector< std::vector<std::string> > getData()
    {
        std::ifstream file(filename_);
        // check for errors
        if(file.fail())
        {
            std::cerr  << "Error Opening File" << std::endl;
            exit(1);
        }

        std::vector<std::vector<std::string>> data;

        std::string line;
        // Iterate through each line and split the content using delimiter
        while (getline(file, line))
        {
            std::vector<std::string> vec {""};
            size_t idx = 0;
            for(char c : line)
            {
                if(c == ','){
                    vec.emplace_back("");
                    idx++;
                }
                else{
                    vec[idx].push_back(c);
                }
            }
            data.push_back(vec);
        }
        // Close the File
        file.close();
        return data;
    };
    
private:
    std::string filename_;
};

class csvParser : public csvReader
{
public:
    // derive the constructor from base class
    using csvReader::csvReader;

    Graph<std::string, float> parse()
    {
        Graph<std::string, float> g;
        const std::vector<std::vector<std::string>> data = getData();

        for(int idx = 0; idx < data.size(); idx++)
        {
            const std::vector<std::string> row = data[idx];
            if(idx == 0){
                for(auto & iter : row){
                    if(!iter.empty()) g.addVertex(iter);
                }
            }
            else{
                for(int idy = 1; idy < row.size(); idy++)
                {
                    if(!row[idy].empty())
                    {
                        g.addEdge(idx-1, idy-1, std::stof(row[idy]));
                    }
                }
            }
        }
        return g;
    };
};

#endif //GRAPH_PARSE_CSV_H
