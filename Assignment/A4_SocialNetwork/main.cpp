#include <iostream>
#include "User.h"
#include "SocialNetwork.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    User u0(0, "Jian");
    User u1(1, "Xin");
    User u2(2, "Yu");
    User u3(3, "Ma");
    User u4(4, "Sheng");
    User u5(5, "Nan");

    u0.addFriend(u1);
    u0.addFriend(u2);

    u1.addFriend(u3);
    u1.addFriend(u4);

    u3.addFriend(u5);

    std::cout << u0.distance(u5);

    return 0;
}
