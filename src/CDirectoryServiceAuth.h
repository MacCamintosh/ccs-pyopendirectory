/**
 * A class that wraps high-level Directory Service calls needed by the
 * CalDAV server.
 **
 * Copyright (c) 2006-2008 Apple Inc. All rights reserved.
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
 **/

#pragma once

#include "CDirectoryService.h"

#include <map>
#include <string>

class CDirectoryServiceAuth : public CDirectoryService
{
public:
    CDirectoryServiceAuth();
    virtual ~CDirectoryServiceAuth();

    bool AuthenticateUserBasic(const char* nodename, const char* user, const char* pswd, bool& result, bool using_python=true);
    bool AuthenticateUserDigest(const char* nodename, const char* user, const char* challenge, const char* response, const char* method, bool& result, bool using_python=true);
    bool AuthenticateUserDigestToActiveDirectory(const char* nodename, const char* user, const char* response, bool& result, bool using_python=true);
	
	CFStringRef GetDigestMD5ChallengeFromActiveDirectory(const char* nodename, bool using_python=true);

protected:

	typedef std::map<std::string, tDirNodeReference> TNodeMap;
	TNodeMap mNodeMap;

    bool NativeAuthenticationBasicToNode(const char* nodename, const char* user, const char* pswd);
    bool NativeAuthenticationDigestToNode(const char* nodename, const char* user, const char* challenge, const char* response, const char* method);
	bool NativeAuthenticationSASLDigestToNode(const char* nodename, const char* user, const char* sasldata, CFStringRef* saslResult = NULL);

    virtual void CloseService();
    virtual tDirNodeReference OpenNamedNode(const char* nodename);
};
