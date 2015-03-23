//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace http {
    namespace server {

        request_handler::request_handler(const std::string& doc_root )
        : doc_root_(doc_root)
        {

        }

        void request_handler::handle_request(const request& req, reply& rep)
        {
            // Decode url to path.
            std::string request_path;
            if (!url_decode(req.uri, request_path))
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }
            //printf("%s \n",request_path.c_str());
            //printf("IN %s \n",req.uri.c_str());
            // Request path must be absolute and not contain "..".
            if (request_path.empty() || request_path[0] != '/'
                || request_path.find("..") != std::string::npos)
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }

            // If path ends in slash (i.e. is a directory) then add "index.html".
            if (request_path[request_path.size() - 1] == '/')
            {
                request_path += "index.html";
            }

            // Determine the file extension.
            std::size_t last_slash_pos = request_path.find_last_of("/");
            std::size_t last_dot_pos = request_path.find_last_of(".");
            std::size_t last_interrogation_pos = request_path.find_last_of("?");
            std::string method_requested = request_path.substr(last_slash_pos,last_interrogation_pos-last_slash_pos);
            std::string extension,parameters;

            //  printf("Method requesed %s \n",method_requested.c_str());
            //std::string req_without_interrogation = request_path.substr(0,last_interrogation_pos);
            if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
            {
                //printf("req_without_interrogation %s",req_without_interrogation.c_str())
                last_dot_pos = method_requested.find_last_of('.');
                extension = method_requested.substr(last_dot_pos + 1,method_requested.size()-last_dot_pos-1);
            }
            if (last_interrogation_pos != std::string::npos && last_interrogation_pos > last_slash_pos)
            {
                parameters = request_path.substr(last_interrogation_pos + 1);
                request_path = request_path.substr(0,last_interrogation_pos);
                //printf("parameters = %s \n", parameters.c_str());
                //printf("%s \n",request_path.c_str());
            }

            //ATTENTION A REFACTORER
            // Open the file to send back.
          /*  if (extension == "snf") {
                snf.computeRequest(request_path.substr(1, last_dot_pos-1), parameters, rep);
            }*/
            else{
                std::string full_path = doc_root_ + request_path;
                std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
                if (!is)
                {
                    rep = reply::stock_reply(reply::not_found);
                    return;
                }

                // Fill out the reply to be sent to the client.
                rep.status = reply::ok;
                char buf[512];
                while (is.read(buf, sizeof(buf)).gcount() > 0)
                    rep.content.append(buf, is.gcount());
                rep.headers.resize(2);
                rep.headers[0].name = "Content-Length";
                rep.headers[0].value = std::to_string(rep.content.size());
                rep.headers[1].name = "Content-Type";
                rep.headers[1].value = mime_types::extension_to_type(extension);
            }

        }

        bool request_handler::url_decode(const std::string& in, std::string& out)
        {
            out.clear();
            out.reserve(in.size());
            for (std::size_t i = 0; i < in.size(); ++i)
            {
                if (in[i] == '%')
                {
                    if (i + 3 <= in.size())
                    {
                        int value = 0;
                        std::istringstream is(in.substr(i + 1, 2));
                        if (is >> std::hex >> value)
                        {
                            out += static_cast<char>(value);
                            i += 2;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (in[i] == '+')
                {
                    out += ' ';
                }
                else
                {
                    out += in[i];
                }
            }
            return true;
        }

    } // namespace server
} // namespace http
