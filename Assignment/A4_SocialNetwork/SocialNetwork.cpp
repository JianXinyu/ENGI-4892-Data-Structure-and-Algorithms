#include "SocialNetwork.h"

SocialNetwork::SocialNetwork()
= default;

//! Add a new user to the social network.
User::ID SocialNetwork::addUser(std::string name)
{
    // the current size of users is the id of the new user.
    User::ID id = users_.size();
    User newUser(id, std::move(name));
    users_.push_back(std::make_shared<User>(newUser));

    return id;
}

/**
 * Add a (bidirectional/undirected) friendship link between two users.
 *
 * @pre the named users actually exist in the social network
 */
SocialNetwork& SocialNetwork::addFriendship(User::ID id1, User::ID id2)
{
    users_[id1]->addFriendPtr(users_[id2]);
    users_[id2]->addFriendPtr(users_[id1]);

    return *this;
}

//! Retrieve a reference to a specific user.
User& SocialNetwork::getUser(User::ID id)
{
    return *(users_[id]);
}

SocialNetwork::Iterator::Iterator(User::ID id, std::shared_ptr<SocialNetwork> network)
    : currentIdx_(id), currentNet_(std::move(network))
{
}

//! An iterator over users in the social network
User& SocialNetwork::Iterator::operator*()
{
    return *(currentNet_->users_[currentIdx_]);
}

SocialNetwork::Iterator SocialNetwork::Iterator::operator ++ (int)
{
    Iterator old = *this;
    if (++currentIdx_ >= currentNet_->users_.size()){
        currentNet_ = nullptr;
    }
    return old;
}

bool SocialNetwork::Iterator::operator == (const Iterator& other) const
{
    if(other.currentNet_ == nullptr)
    {
        return currentNet_ ? false : true;
    }
    return (currentNet_.get() == other.currentNet_.get()) && (currentIdx_ == other.currentIdx_);
}

bool SocialNetwork::Iterator::operator != (const Iterator& other) const
{
    if(other.currentNet_ == nullptr)
    {
        return currentNet_ ? true : false;
    }
    return (currentNet_.get() != other.currentNet_.get()) || (currentIdx_ != other.currentIdx_);
}
//! Get an iterator over all users in the network.
SocialNetwork::Iterator SocialNetwork::begin()
{
    return Iterator(0, std::make_shared<SocialNetwork>(*this));
}

//! Find all users in the network whose names start with `name`.
SocialNetwork::Iterator SocialNetwork::find(const std::string& name)
{
    SocialNetwork result;

    for (const auto& user : users_)
    {
        if (user->name().find(name)==0)
        {
            result.addUser(user->name());
        }
    }

    return Iterator(0, std::make_shared<SocialNetwork>(result));
}

//! Get an iterator that signifies the end of any user iteration.
SocialNetwork::Iterator SocialNetwork::end()
{
    return Iterator(users_.size(), nullptr);
}
