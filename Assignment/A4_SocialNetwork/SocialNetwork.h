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

#ifndef SOCIAL_NETWORK_H_
#define SOCIAL_NETWORK_H_

#include "User.h"


/**
 * A (rather crude!) representation of a social network.
 */
class SocialNetwork
{
public:
    //! Add a new user to the social network.
    User::ID addUser(std::string name);

    /**
     * Add a (bidirectional/undirected) friendship link between two users.
     *
     * @pre the named users actually exist in the social network
     */
    SocialNetwork& addFriendship(User::ID, User::ID);

    //! Retrieve a reference to a specific user.
    User& getUser(User::ID);

    //! An iterator over users in the social network
    struct Iterator
    {
        User& operator*();
        Iterator operator ++ (int);

        bool operator == (const Iterator&) const;
        bool operator != (const Iterator&) const;
    };

    //! Get an iterator over all users in the network.
    Iterator begin();

    //! Find all users in the network whose names start with `name`.
    Iterator find(std::string name);

    //! Get an iterator that signifies the end of any user iteration.
    Iterator end();


};

#endif