//
//  Created by Jeremy Fonseca on September, 2022
//

#include "Includes/Repositories/AuthenticationRepository.hpp"
#include "Includes/Models/UserModel.hpp"

using namespace Server::Repositories;
using namespace Server::Models;
using namespace bsoncxx::builder::basic;

AuthenticationRepository::AuthenticationRepository()
{
  this->m_Connection = mongocxx::client{mongocxx::uri{"mongodb+srv://fontseca:L6wmddLHjhk3SNF9@personal.l3tcooi.mongodb.net/?retryWrites=true&w=majority"}};
  this->m_Database = this->m_Connection["EcosystemOfServices"];
}

bool AuthenticationRepository::SignupUser(const UserModel &user) const noexcept
{
  auto builder = bsoncxx::builder::stream::document{};

  // Continue if not repeated.
  if (this->m_Database.collection("user").find_one(make_document(kvp("email", user.Email))))
    return false;

  bsoncxx::document::value user_doc =
      builder << "email" << user.Email
              << "password" << user.Password
              << bsoncxx::builder::stream::finalize;

  this->m_Database.collection("user").insert_one(user_doc.view());
  return true;
}

bool AuthenticationRepository::LoginUser(const UserModel &user) const
{
  if (!this->m_Database.collection("user").find_one(make_document(kvp("email", user.Email))))
    throw std::runtime_error("Error: User does not exist. Try signing up first.");

  if (!this->m_Database.collection("user").find_one(make_document(kvp("password", user.Password))))
    throw std::runtime_error("Error: Wrong password!");

  auto builder = bsoncxx::builder::stream::document{};
  bsoncxx::document::value user_doc =
      builder << "email" << user.Email
              << "password" << user.Password
              << bsoncxx::builder::stream::finalize;

  const auto maybe = this->m_Database.collection("user").find_one(user_doc.view());

  if (maybe)
    return true;
  return false;
}