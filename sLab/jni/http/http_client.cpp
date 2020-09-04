/*
 * http_client.cpp
 *
 *  Created on: 2018年11月29日
 *      Author: pengzc
 */

#include "http_client.h"

#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include "utils/log.h"

using std::fstream;

namespace http {

HttpClient::HttpClient() {
}

HttpClient::~HttpClient() {
}

string http::HttpClient::Download(const std::string& url, int port,
        std::string path_to_save) {
    string hostname = url.substr(0, url.find('/', 0));
    int status;
    struct addrinfo host_info; // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

    // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
    // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
    // is created in c++, it will be given a block of memory. This memory is not nessesary
    // empty. Therefor we use the memset function to make sure all fields are NULL.
    memset(&host_info, 0, sizeof host_info);

    host_info.ai_family = AF_UNSPEC;   // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    // Now fill up the linked list of host_info structs with google's address information.
    //status = getaddrinfo("www.google.com", "80", &host_info, &host_info_list);
    status = getaddrinfo(hostname.c_str(), ToString(port).c_str(), &host_info,
            &host_info_list);
    // getaddrinfo returns 0 on succes, or some other value when an error occured.
    // (translated into human readable text by the gai_gai_strerror function).
    if (status != 0) {
        //std::cout << "getaddrinfo error" << gai_strerror(status) ;
        return std::string("ERROR: Hostname could not be resolved");
    }

    //std::cout << "Creating a socket..."  << std::endl;
    int socketfd; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
            host_info_list->ai_protocol);
    if (socketfd == -1) {
        freeaddrinfo(host_info_list);
        return std::string("ERROR: Could not open socket");
    }

    status = connect(socketfd, host_info_list->ai_addr,
            host_info_list->ai_addrlen);
    if (status == -1) {
        close(socketfd);
        freeaddrinfo(host_info_list);
        return std::string("ERROR: Could not connect");
    }

    string connection = "Close";
    string cache = "";
    string accept =
            "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8";
    string user_agent =
            "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.154 Safari/537.36 LBBROWSER";
    string referer = "";
    string ifnonematch = "";

    string request = "GET " + url.substr(url.find('/', 0), url.length() - 1) + " HTTP/1.1\r\nHost:" + hostname
            + "\r\nConnection:" + connection + "\r\nAccept: " + accept
            + "\r\nUser-Agent: " + user_agent + "\r\nReferer: " + "\r\n\r\n";

    if (((int)request.size()) != send(socketfd, request.c_str(), request.size(), 0)) {
        close(socketfd);
        freeaddrinfo(host_info_list);
        return "ERROR: send request error";
    }

    #define RECV_BUF_LENTH 2048

    char buf[RECV_BUF_LENTH] = { 0 };
    int recv_length = 0;
    recv_length = recv(socketfd, buf, RECV_BUF_LENTH - sizeof(char), 0);
    /*
     * 这里是想一次接收1024字节，将HTTP Head 再过滤掉，
     */
    char* cpos = strstr(buf, "\r\n\r\n");
    if (cpos == NULL) {
        close(socketfd);
        freeaddrinfo(host_info_list);
        LOGD("cpos is null, head is %d ", recv_length);
        return "ERROR: Head less";
    }

    fstream file;
    file.open(path_to_save.c_str(), std::ios::out | std::ios::binary);
    file.write(cpos + strlen("\r\n\r\n"),
            recv_length - (cpos - buf) - strlen("\r\n\r\n"));
    int recv_buf_len = RECV_BUF_LENTH - sizeof(char);

    string error_message;
    while (true) {
        recv_length = recv(socketfd, buf, recv_buf_len, 0);


        if (recv_length == 0) {

            string temp = buf;
            if(temp.size() != 0)
                error_message = "ERROR: " + temp.substr(0, temp.find('\n',0));
            break;
        } else if (recv_length < 0) {
            if ((errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)) {
                continue;
            } else {
                //出错
                error_message = "ERROR: recv exception";
                break;
            }
        } else if (recv_length > 0) {
            try {
                file.write(buf, recv_length);
                memset(buf,0,recv_length);
//                for(int k = 0; k < recv_length; k++)
//                	buf[k]=0;
            } catch (...) { //what's the catch effect?
                error_message = "ERROR: write file exception";
                break;
            }
        }
    }

    file.flush();
    file.close();
    freeaddrinfo(host_info_list);
    close(socketfd);
//    if(error_message != "")
//    {
//    	string cmd = "rm " + path_to_save;
//        system(cmd.c_str());
//    }
    return error_message;
}

string HttpClient::ToString(int i) {
    std::stringstream stream;
    stream << i;
    return stream.str();
}

} /* namespace http */

