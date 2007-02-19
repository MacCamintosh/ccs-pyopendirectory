/**
 * A class that wraps high-level Directory Service calls needed by the
 * CalDAV server.
 **
 * Copyright (c) 2006-2007 Apple Inc. All rights reserved.
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
 *
 * DRI: Cyrus Daboo, cdaboo@apple.com
 **/

#pragma once

#include <CoreFoundation/CoreFoundation.h>
#include <DirectoryService/DirectoryService.h>

class CFStringUtil;

class CDirectoryService
{
public:
	CDirectoryService(const char* nodename);
	~CDirectoryService();
	
	CFMutableDictionaryRef ListAllRecordsWithAttributes(const char* recordType, CFArrayRef attributes);
	CFMutableDictionaryRef QueryRecordsWithAttributes(CFDictionaryRef query, int matchType, bool casei, bool allmatch, const char* recordType, CFArrayRef attributes);

	bool AuthenticateUserBasic(const char* guid, const char* user, const char* pswd, bool& result);
	bool AuthenticateUserDigest(const char* guid, const char* user, const char* challenge, const char* response, const char* method, bool& result);
	
private:
	const char*			mNodeName;
	tDirReference		mDir;
	tDirNodeReference	mNode;
	tDataBufferPtr		mData;
	UInt32				mDataSize;
	
	CFMutableDictionaryRef _ListAllRecordsWithAttributes(const char* type, CFArrayRef names, CFArrayRef attrs);
	CFMutableDictionaryRef _QueryRecordsWithAttributes(CFDictionaryRef query, int matchType, bool casei, bool allmatch, const char* recordType, CFArrayRef attributes);

	CFStringRef CDirectoryService::AuthenticationGetNode(const char* guid);
	bool NativeAuthenticationBasic(const char* guid, const char* user, const char* pswd);
	bool NativeAuthenticationBasicToNode(const char* nodename, const char* user, const char* pswd);
	bool NativeAuthenticationDigest(const char* guid, const char* user, const char* challenge, const char* response, const char* method);
	bool NativeAuthenticationDigestToNode(const char* nodename, const char* user, const char* challenge, const char* response, const char* method);
	
	void OpenService();
	void CloseService();
	
	void OpenNode();
	tDirNodeReference OpenNamedNode(const char* nodename);
	void CloseNode();
	
	void CreateBuffer();
	void RemoveBuffer();
	void ReallocBuffer();

	void BuildStringDataList(CFArrayRef strs, tDataListPtr data);
	
	void BuildSimpleQuery(CFDictionaryRef dict, tDataNodePtr& attr, tDataNodePtr& value);
	void BuildCompoundQuery(CFDictionaryRef dict, tDirPatternMatch matchType, bool allmatch, tDataNodePtr& value);

	char* CStringFromBuffer(tDataBufferPtr data);
	char* CStringFromData(const char* data, size_t len);
};