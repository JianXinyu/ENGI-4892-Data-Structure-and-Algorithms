#include "User.h"

User::User(User::ID id, std::string name)
        : id_(id), name_(std::move(name))
{
}

User::User()
{
}

//! What is this user's ID?
User::ID User::id() const
{
    return id_;
}

//! what is the user's name?
std::string User::name() const
{
    return name_;
}

//! How many friends does this user have?
size_t User::degree() const
{
    return friends_.size();
}

/**
 * What is the shortest path to the given User from this one?
 *
 * @returns   the number of friend links between this User and that
 *            one, or SIZE_MAX if there is no connection between them
 */
size_t User::distance(const User& target) const
{
    // if this User is the given User, we already get there
    if(*this == target) return 0;

    std::map<ID, size_t> distances;
    std::queue<std::shared_ptr<User>> worklist;

    distances[id_] = 0;
    worklist.push(std::make_shared<User>(*this));

    while (!worklist.empty())
    {
        std::shared_ptr<User> current = std::move(worklist.front());
        worklist.pop();

//        for(auto iter = current->friends_.begin(); iter != current->friends_.end(); iter++)
        for(const std::shared_ptr<User>& frd : current->friends_)
        {
//            if(!distances.count(frd->id_))
            if(distances.find(frd->id_) == distances.end())
            {
                distances[frd->id_] = distances[current->id_] + 1;
                if(frd->id_ == target.id_)
                    return distances[frd->id_];
                worklist.push(frd);
            }
        }
    }
    return SIZE_MAX;
}

//! Make this User friends with another User.
void User::addFriend(const User& other)
{
    friends_.push_back(std::make_shared<User>(other));
}

void User::addFriendPtr(std::shared_ptr<User> other)
{
    friends_.push_back(other);
}

User::FriendIterator::FriendIterator(int id, std::shared_ptr<User> user)
        : frdIdx_(id), currentUser_(std::move(user))
{
}

User& User::FriendIterator::operator*()
{
    return *currentUser_->friends_[frdIdx_];
}

User::FriendIterator User::FriendIterator::operator ++ (int)
{
    FriendIterator old = *this;
    if(++frdIdx_ >= currentUser_->friends_.size())
        currentUser_ = nullptr;
    return old;
}

bool User::FriendIterator::operator == (const User::FriendIterator& other) const
{
    if(other.currentUser_ == nullptr)
        return currentUser_ ? false : true;
    return (currentUser_.get() == other.currentUser_.get()) && (frdIdx_ == other.frdIdx_);
}

bool User::FriendIterator::operator != (const User::FriendIterator& other) const
{
    if(other.currentUser_ == nullptr)
        return currentUser_ ? true : false;
    return (currentUser_.get() != other.currentUser_.get()) || (frdIdx_ != other.frdIdx_);
}

//! Get an iterator that will iterate over this User's friends
User::FriendIterator User::begin() const
{
    return FriendIterator(0, std::make_shared<User>(*this));
}

/**
 * Get an iterator that will iterate over this User's friends
 * as well as **their** friends.
 *
 * The resulting iterator should iterate over all of this user's friends
 * and friends of friends in no particular order. This user (i.e., the
 * centre of the egonet) should not show up in the iteration, and no
 * single user should be iterated over more than once.
 */
User::FriendIterator User::friendsOfFriends() const
{
    User fof; // a temp User that field friends_ contains all friends of this->friends
    std::vector<ID> rcd;

    for(const auto& frd : friends_)
    {
        // First, add friend in this->friends_ into fof.friends_
        fof.addFriend(*frd);
        rcd.push_back(frd->id_);
        // Second, add all friend of the above friend into fof.friends_
        for(const auto& subFrd : frd->friends_)
        {
            // if subFrd wasn't added before and subFrd isn't self, add it
            if(std::find(rcd.begin(), rcd.end(), subFrd->id_) == rcd.end()
                && subFrd->id_!=id_)
            {
                fof.addFriend(*subFrd);
                rcd.push_back(subFrd->id_);
            }
        }
    }
    return FriendIterator(0, std::make_shared<User>(fof));
}

//! Get an iterator that signifies the end of any friend iteration.
User::FriendIterator User::end() const
{
    return FriendIterator(friends_.size(), nullptr);
}

