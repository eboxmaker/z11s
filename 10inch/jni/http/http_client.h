/*
 * http_client.h
 *
 *  Created on: 2018年11月29日
 *      Author: pengzc
 */

#ifndef JNI_HTTP_HTTP_CLIENT_H_
#define JNI_HTTP_HTTP_CLIENT_H_


#include <string>
using std::string;

#include "utils/Log.h"

namespace http {

class HttpClient {
public:
    HttpClient();
    virtual ~HttpClient();
    string Download(const std::string& url, int host_port, std::string path_to_save);

private:
    string ToString(int i);
};

} /* namespace std */

#endif /* JNI_HTTP_HTTP_CLIENT_H_ */
