#include <iostream>
#include "User.h"
#include "SocialNetwork.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    SocialNetwork net;
    // test User::find()
//    net.addUser("Albert");
//    net.addUser("Alice" );
//    net.addUser("Allison");
//    net.addUser("Ali");
//    net.addUser("Art");
//    net.addUser("Bob");

//    SocialNetwork::Iterator itr = net.find("");

    // test User::begin()
//    net.addUser("Alice" );
//    net.addUser("Bob");
//    net.addUser("Charlie");
//    net.addFriendship(0, 1);
//    net.addFriendship(0, 2);
//    User alice = net.getUser(0);
//    auto itr = alice.begin();
//    User u1 = *itr;
//    itr++;
//    User u2 = *itr;

    // test User::friendsOfFriends()
    net.addUser("Alice" );
    net.addUser("Bob");
    net.addUser("Charlie");
    net.addUser("Dave");
    net.addFriendship(0, 1);
    net.addFriendship(1, 2);
    net.addFriendship(2, 3);
    User alice = net.getUser(0);
    auto itr = alice.friendsOfFriends();
    return 0;
}
