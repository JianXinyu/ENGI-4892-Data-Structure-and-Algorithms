
/*
 * Copyright 2018, 2020 Jonathan Anderson, 2020 Xinyu Jian
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef USER_H_
#define USER_H_

#include <cstddef>      // for definition of size_t
#include <memory>       // std::shared_ptr
#include <vector>       // std::vector
#include <queue>        // std::queue
#include <map>          // std::map
#include <algorithm>    // std::find
/**
 * Representation of a social network user.
 */
class User
{
public:
    using ID = size_t;

    User(ID id, std::string name);
    User();

    //! What is this user's ID?
    ID id() const;

    //! How many friends does this user have?
    size_t degree() const;

    /**
     * What is the shortest path to the given User from this one?
     *
     * @returns   the number of friend links between this User and that
     *            one, or SIZE_MAX if there is no connection between them
     */
    size_t distance(const User&) const;

    //! Make this User friends with another User.
    void addFriend(const User&);

    //! An iterator that can iterate over all of a User's friends
    struct FriendIterator
    {
        FriendIterator(int id, std::shared_ptr<User> user);
        User& operator*();
        FriendIterator operator ++ (int);

        bool operator == (const FriendIterator&) const;
        bool operator != (const FriendIterator&) const;

        std::shared_ptr<User> currentUser_;
        int frdIdx_; // friend index in the friends_ vector
    };

    //! Get an iterator that will iterate over this User's friends
    FriendIterator begin() const;

    /**
     * Get an iterator that will iterate over this User's friends
     * as well as **their** friends.
     *
     * The resulting iterator should iterate over all of this user's friends
     * and friends of friends in no particular order. This user (i.e., the
     * centre of the egonet) should not show up in the iteration, and no
     * single user should be iterated over more than once.
     */
    FriendIterator friendsOfFriends() const;

    //! Get an iterator that signifies the end of any friend iteration.
    FriendIterator end() const;

private:
    ID id_;
    std::string name_;
    std::vector<std::shared_ptr<User>> friends_;

    bool operator == (const User& other) const { return id_ == other.id_; }
    bool operator != (const User& other) const { return id_ != other.id_; }
};

#endif