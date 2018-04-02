//
//  CatenisApiClient.cpp
//  CatenisAPIClientCpp
//
//  Created by Sungwoo Bae on 5/25/17.
//  Modifications by R. Benson Evans on 2/20/2018.
//

#include <iostream>
#include <string>
#include <map>

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
#include <json-spirit/json_spirit_value.h>
#elif defined(COM_SUPPORT_LIB_POCO)
#include <Poco/JSON/Object.h>
#endif

#include <CatenisApiException.h>
#include <CatenisApiInternals.h>
#include <CatenisApiClient.h>


// API Method: Log Message
void ctn::CtnApiClient::logMessage(LogMessageResult &data, std::string message, const MessageOptions &option)
{
    std::map<std::string, std::string> params;
    std::map<std::string, std::string> queries;

    // write request body
#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
    json_spirit::mObject objData;

    objData["message"] = message;

    json_spirit::mObject objOptions;

    objOptions["encoding"] = option.encoding;
    objOptions["encrypt"] = option.encrypt;
    objOptions["storage"] = option.storage;

    objData["options"] = objOptions;

    json_spirit::mValue request_data(objData);
#elif defined(COM_SUPPORT_LIB_POCO)
    Poco::JSON::Object request_data;

    request_data.set("message", message);

    Poco::JSON::Object options;
    options.set("encoding", option.encoding);
    options.set("encrypt", option.encrypt);
    options.set("storage", option.storage);
    request_data.set("options", options);
#endif

    std::string http_return_data;
    this->internals_->httpRequest("POST", "messages/log", params, queries, request_data, http_return_data);
    this->internals_->parseLogMessage(data, http_return_data);
}

// API Method: Send Message
void ctn::CtnApiClient::sendMessage(SendMessageResult &data, const Device &device, std::string message, const MessageOptions&option)
{
    std::map<std::string, std::string> params;
    std::map<std::string, std::string> queries;

    // write request body
#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
    json_spirit::mObject objData;

    json_spirit::mObject objTargetDevice;

    objTargetDevice["id"] = device.device_id;
    objTargetDevice["isProdUniqueId"] = device.is_prod_uniqueid;

    objData["targetDevice"] = objTargetDevice;

    objData["message"] = message;

    json_spirit::mObject objOptions;

    objOptions["readConfirmation"] = option.readConfirmation;
    objOptions["encoding"] = option.encoding;
    objOptions["encrypt"] = option.encrypt;
    objOptions["storage"] = option.storage;

    objData["options"] = objOptions;

    json_spirit::mValue request_data(objData);
#elif defined(COM_SUPPORT_LIB_POCO)
    Poco::JSON::Object request_data;

    Poco::JSON::Object targetD;
    targetD.set("id", device.device_id);
    targetD.set("isProdUniqueId", device.is_prod_uniqueid);
    request_data.set("targetDevice", targetD);

    request_data.set("message", message);

    Poco::JSON::Object options;
    options.set("readConfirmation", option.readConfirmation);
    options.set("encoding", option.encoding);
    options.set("encrypt", option.encrypt);
    options.set("storage", option.storage);
    request_data.set("options", options);
#endif

    std::string http_return_data;
    this->internals_->httpRequest("POST", "messages/send", params, queries, request_data, http_return_data);
    this->internals_->parseSendMessage(data, http_return_data); 
}

// API Method: Read Message
void ctn::CtnApiClient::readMessage(ReadMessageResult &data, std::string message_id, std::string encoding)
{
    std::map<std::string, std::string> params;
    std::map<std::string, std::string> queries;

    params[":messageId"] = message_id;
    queries["encoding"] = encoding;

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
    json_spirit::mValue request_data;
#elif defined(COM_SUPPORT_LIB_POCO)
    Poco::JSON::Object request_data;
#endif

    std::string http_return_data;
    this->internals_->httpRequest("GET", "messages/:messageId", params, queries, request_data, http_return_data);
    this->internals_->parseReadMessage(data, http_return_data); 
}

// API Method: Retreive Message Containter
void ctn::CtnApiClient::retrieveMessageContainer(RetrieveMessageContainerResult &data, std::string message_id)
{
    std::map<std::string, std::string> params;
    std::map<std::string, std::string> queries;

    params[":messageId"] = message_id;

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
    json_spirit::mValue request_data;
#elif defined(COM_SUPPORT_LIB_POCO)
    Poco::JSON::Object request_data;
#endif

    std::string http_return_data;
    this->internals_->httpRequest("GET", "messages/:messageId/container", params, queries, request_data, http_return_data);
    this->internals_->parseRetrieveMessageContainer(data, http_return_data); 
}

// API Method: List Messages
void ctn::CtnApiClient::listMessages(ListMessagesResult &data, std::string action, std::string direction, std::string from_device_ids, std::string to_device_ids, std::string from_device_prod_ids, std::string to_device_prod_ids, std::string read_state, std::string start_date, std::string endDate)
{
    std::map<std::string, std::string> params;
    std::map<std::string, std::string> queries;

    queries["action"] = action;
    queries["direction"] = direction;
    
    if(!from_device_ids.empty()) queries["fromDeviceIds"] = from_device_ids;
    if(!to_device_ids.empty()) queries["toDeviceIds"] = to_device_ids;
    if(!from_device_prod_ids.empty()) queries["fromDeviceProdUniqueIds"] = from_device_prod_ids;
    if(!to_device_prod_ids.empty()) queries["toDeviceProdUniqueIds"] = to_device_prod_ids;
    
    queries["readState"] = read_state;
    
    if(!start_date.empty()) queries["startDate"] = start_date;
    if(!endDate.empty()) queries["endDate"] = endDate;

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
    json_spirit::mValue request_data;
#elif defined(COM_SUPPORT_LIB_POCO)
    Poco::JSON::Object request_data;
#endif

    std::string http_return_data;
    this->internals_->httpRequest("GET", "messages", params, queries, request_data, http_return_data);
    this->internals_->parseListMessages(data, http_return_data);
}

// API Method: List Permission Events
void ctn::CtnApiClient::listPermissionEvents(ListPermissionEventsResult &data)
{
	std::map<std::string, std::string> params;
	std::map<std::string, std::string> queries;

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
	json_spirit::mValue request_data;
#elif defined(COM_SUPPORT_LIB_POCO)
	Poco::JSON::Object request_data;
#endif
	std::string http_return_data;
	this->internals_->httpRequest("GET", "permission/events", params, queries, request_data, http_return_data);
	this->internals_->parseListPermissionEvents(data, http_return_data);
}

// API Method: Retrieve Permission Rights
void ctn::CtnApiClient::retrievePermissionRights(RetrievePermissionRightsResult &data, std::string eventName)
{
	std::map<std::string, std::string> params;
	std::map<std::string, std::string> queries;

	params[":eventName"] = eventName;

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
	json_spirit::mValue request_data;
#elif defined(COM_SUPPORT_LIB_POCO)
	Poco::JSON::Object request_data;
#endif
	std::string http_return_data;
	this->internals_->httpRequest("GET", "permission/events/:eventName/rights", params, queries, request_data, http_return_data);
	this->internals_->parseRetrievePermissionRights(data, http_return_data);
}

// API Method: Set Permission Rights
void ctn::CtnApiClient::setPermissionRights(SetPermissionRightsResult &data, std::string eventName, std::string system, std::shared_ptr<SetRightsCtnNode> ctnNodeObj = nullptr, std::shared_ptr<SetRightsClient> clientObj = nullptr, std::shared_ptr<SetRightsDevice> deviceObj = nullptr)
{
	std::map<std::string, std::string> params;
	std::map<std::string, std::string> queries;

	params[":eventName"] = eventName;

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
	json_spirit::mObject objData;

	std::list<std::string> allowed;
	std::list<std::string> denied;

	// //////////////////////////// Prepare JSON for System Level ////////////////////////////////
	if (!system.empty())
		objData["system"] = system;

	// //////////////////////////// Prepare JSON for Catenis Node Level ////////////////////////////////
	if (ctnNodeObj != nullptr)
	{
		json_spirit::mObject ctnNode;

		if (ctnNodeObj->allowed.size() > 0)
		{
			json_spirit::mArray allowCtnNode;
			for (std::list<std::string>::const_iterator i = ctnNodeObj->allowed.begin(); i != ctnNodeObj->allowed.end(); ++i)
			{
				if (!(*i).empty())
					allowCtnNode.push_back(*i);
			}
			if (allowCtnNode.size() > 0)
				ctnNode["allow"] = allowCtnNode;
		}
		if (ctnNodeObj->denied.size() > 0)
		{
			json_spirit::mArray denyCtnNode;
			for (std::list<std::string>::const_iterator i = ctnNodeObj->denied.begin(); i != ctnNodeObj->denied.end(); ++i)
			{
				if (!(*i).empty())
					denyCtnNode.push_back(*i);
			}
			if (denyCtnNode.size() > 0)
				ctnNode["deny"] = denyCtnNode;
		}
		if (ctnNodeObj->revoked.size() > 0)
		{
			json_spirit::mArray revokeCtnNode;
			for (std::list<std::string>::const_iterator i = ctnNodeObj->revoked.begin(); i != ctnNodeObj->revoked.end(); ++i)
			{
				if (!(*i).empty())
					revokeCtnNode.push_back(*i);
			}
			if (revokeCtnNode.size() > 0)
				ctnNode["none"] = revokeCtnNode;
		}
		objData["catenisNode"] = ctnNode;
	}


	// //////////////////////////// Prepare JSON for Client Level ////////////////////////////////
	if (clientObj != nullptr)
	{
		json_spirit::mObject client;

		if (clientObj->allowed.size() > 0)
		{
			json_spirit::mArray allowClient;
			for (std::list<std::string>::const_iterator i = clientObj->allowed.begin(); i != clientObj->allowed.end(); ++i)
			{
				if (!(*i).empty())
					allowClient.push_back(*i);
			}
			if (allowClient.size() > 0)
				client["allow"] = allowClient;
		}
		if (clientObj->denied.size() > 0)
		{
			json_spirit::mArray denyClient;
			for (std::list<std::string>::const_iterator i = clientObj->denied.begin(); i != clientObj->denied.end(); ++i)
			{
				if (!(*i).empty())
					denyClient.push_back(*i);
			}
			if (denyClient.size() > 0)
				client["deny"] = denyClient;
		}
		if (clientObj->revoked.size() > 0)
		{
			json_spirit::mArray revokeClient;
			for (std::list<std::string>::const_iterator i = clientObj->revoked.begin(); i != clientObj->revoked.end(); ++i)
			{
				if (!(*i).empty())
					revokeClient.push_back(*i);
			}
			if (revokeClient.size() > 0)
				client["none"] = revokeClient;
		}
		objData["client"] = client;
	}

	// //////////////////////////// Prepare JSON for Device Level ////////////////////////////////
	if (deviceObj != nullptr)
	{
		json_spirit::mObject device;
		if (deviceObj->allowed.size() > 0)
		{
			json_spirit::mArray allowDevice;
			json_spirit::mObject tmpObj;
			for (std::list<std::shared_ptr<SetRightsDeviceInfo>>::iterator i = deviceObj->allowed.begin(); i != deviceObj->allowed.end(); ++i)
			{
				if (!(*(*i)).id.empty())
				{
					tmpObj["id"] = (*(*i)).id;
					tmpObj["isProdUniqueId"] = (*(*i)).isProdUniqueId;
					allowDevice.push_back(tmpObj);
				}
			}
			if (allowDevice.size() > 0)
				device["allow"] = allowDevice;
		}
		if (deviceObj->denied.size() > 0)
		{
			json_spirit::mArray denyDevice;
			json_spirit::mObject tmpObj;
			for (std::list<std::shared_ptr<SetRightsDeviceInfo>>::iterator i = deviceObj->denied.begin(); i != deviceObj->denied.end(); ++i)
			{
				if (!(*(*i)).id.empty())
				{
					tmpObj["id"] = (*(*i)).id;
					tmpObj["isProdUniqueId"] = (*(*i)).isProdUniqueId;
					denyDevice.push_back(tmpObj);
				}
			}
			if (denyDevice.size() > 0)
				device["deny"] = denyDevice;
		}
		if (deviceObj->revoked.size() > 0)
		{
			json_spirit::mArray revokeDevice;
			json_spirit::mObject tmpObj;
			for (std::list<std::shared_ptr<SetRightsDeviceInfo>>::iterator i = deviceObj->revoked.begin(); i != deviceObj->revoked.end(); ++i)
			{
				if (!(*(*i)).id.empty())
				{
					tmpObj["id"] = (*(*i)).id;
					tmpObj["isProdUniqueId"] = (*(*i)).isProdUniqueId;
					revokeDevice.push_back(tmpObj);
				}
			}
			if (revokeDevice.size() > 0)
				device["none"] = revokeDevice;
		}
		objData["device"] = device;
	}

	json_spirit::mValue request_data(objData);

#elif defined(COM_SUPPORT_LIB_POCO)
	Poco::JSON::Object request_data;

	std::list<std::string> allowed;
	std::list<std::string> denied;

	// //////////////////////////// Prepare JSON for System Level ////////////////////////////////
	if (!system.empty())
		request_data.set("system", system);

	// //////////////////////////// Prepare JSON for Catenis Node Level ////////////////////////////////
	if (ctnNodeObj != nullptr)
	{
		Poco::JSON::Object ctnNode;
		if (ctnNodeObj->allowed.size() > 0)
		{
			Poco::JSON::Array allowCtnNode;
			for (std::list<std::string>::const_iterator i = ctnNodeObj->allowed.begin(); i != ctnNodeObj->allowed.end(); ++i)
			{
				if (!(*i).empty())
					allowCtnNode.add(*i);
			}
			if(allowCtnNode.size() > 0)
				ctnNode.set("allow", allowCtnNode);
		}
		if (ctnNodeObj->denied.size() > 0)
		{
			Poco::JSON::Array denyCtnNode;
			for (std::list<std::string>::const_iterator i = ctnNodeObj->denied.begin(); i != ctnNodeObj->denied.end(); ++i)
			{
				if (!(*i).empty())
					denyCtnNode.add(*i);
			}
			if (denyCtnNode.size() > 0)
				ctnNode.set("deny", denyCtnNode);
		}
		if (ctnNodeObj->revoked.size() > 0)
		{
			Poco::JSON::Array revokeCtnNode;
			for (std::list<std::string>::const_iterator i = ctnNodeObj->revoked.begin(); i != ctnNodeObj->revoked.end(); ++i)
			{
				if (!(*i).empty())
					revokeCtnNode.add(*i);
			}
			if (revokeCtnNode.size() > 0)
				ctnNode.set("none", revokeCtnNode);
		}
		request_data.set("catenisNode", ctnNode);
	}

	// //////////////////////////// Prepare JSON for Client Level ////////////////////////////////
	if (clientObj != nullptr)
	{
		Poco::JSON::Object client;
		if (clientObj->allowed.size() > 0)
		{
			Poco::JSON::Array allowClient;
			for (std::list<std::string>::const_iterator i = clientObj->allowed.begin(); i != clientObj->allowed.end(); ++i)
			{
				if (!(*i).empty())
					allowClient.add(*i);
			}
			if (allowClient.size() > 0)
				client.set("allow", allowClient);
		}
		if (clientObj->denied.size() > 0)
		{
			Poco::JSON::Array denyClient;
			for (std::list<std::string>::const_iterator i = clientObj->denied.begin(); i != clientObj->denied.end(); ++i)
			{
				if (!(*i).empty())
					denyClient.add(*i);
			}
			if (denyClient.size() > 0)
				client.set("deny", denyClient);
		}
		if (clientObj->revoked.size() > 0)
		{
			Poco::JSON::Array revokeClient;
			for (std::list<std::string>::const_iterator i = clientObj->revoked.begin(); i != clientObj->revoked.end(); ++i)
			{
				if (!(*i).empty())
					revokeClient.add(*i);
			}
			if (revokeClient.size() > 0)
				client.set("none", revokeClient);
		}
		request_data.set("client", client);
	}

	// //////////////////////////// Prepare JSON for Device Level ////////////////////////////////
	if (deviceObj != nullptr)
	{
		Poco::JSON::Object device;
		if (deviceObj->allowed.size() > 0)
		{			
			Poco::JSON::Array allowDevice;
			Poco::JSON::Object tmpObj;
			for (std::list<std::shared_ptr<SetRightsDeviceInfo>>::iterator i = deviceObj->allowed.begin(); i != deviceObj->allowed.end(); ++i)
			{
				if (!(*(*i)).id.empty())
				{
					tmpObj.set("id", (*(*i)).id);
					tmpObj.set("isProdUniqueId", (*(*i)).isProdUniqueId);
					allowDevice.add(tmpObj);
				}
			}
			if (allowDevice.size() > 0)
				device.set("allow", allowDevice);
		}
		if (deviceObj->denied.size() > 0)
		{
			Poco::JSON::Array denyDevice;
			Poco::JSON::Object tmpObj;
			for (std::list<std::shared_ptr<SetRightsDeviceInfo>>::iterator i = deviceObj->denied.begin(); i != deviceObj->denied.end(); ++i)
			{
				if (!(*(*i)).id.empty())
				{
					tmpObj.set("id", (*(*i)).id);
					tmpObj.set("isProdUniqueId", (*(*i)).isProdUniqueId);
					denyDevice.add(tmpObj);
				}
			}
			if (denyDevice.size() > 0)
				device.set("deny", denyDevice);
		}
		if (deviceObj->revoked.size() > 0)
		{
			Poco::JSON::Array revokeDevice;
			Poco::JSON::Object tmpObj;
			for (std::list<std::shared_ptr<SetRightsDeviceInfo>>::iterator i = deviceObj->revoked.begin(); i != deviceObj->revoked.end(); ++i)
			{
				if (!(*(*i)).id.empty())
				{
					tmpObj.set("id", (*(*i)).id);
					tmpObj.set("isProdUniqueId", (*(*i)).isProdUniqueId);
					revokeDevice.add(tmpObj);
				}
			}
			if (revokeDevice.size() > 0)
				device.set("none", revokeDevice);
		}
		request_data.set("device", device);
	}

#endif
	std::string http_return_data;
	this->internals_->httpRequest("POST", "permission/events/:eventName/rights", params, queries, request_data, http_return_data);
	this->internals_->parseSetPermissionRights(data, http_return_data);
}

// API Method: List Notification Events
void ctn::CtnApiClient::listNotificationEvents(ListNotificationEventsResult &data)
{
	std::map<std::string, std::string> params;
	std::map<std::string, std::string> queries;

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
	json_spirit::mValue request_data;
#elif defined(COM_SUPPORT_LIB_POCO)
	Poco::JSON::Object request_data;
#endif
	std::string http_return_data;
	this->internals_->httpRequest("GET", "notification/events", params, queries, request_data, http_return_data);
	this->internals_->parseListNotificationEvents(data, http_return_data);
}

// API Method: Check Effective Permission Events
void ctn::CtnApiClient::checkEffectivePermissionRight(CheckEffectivePermissionRightResult &data, std::string eventName, std::string deviceId, std::string isProdUniqueId = "false")
{

	std::map<std::string, std::string> params;
	std::map<std::string, std::string> queries;

	queries["isProdUniqueId"] = "false"; // isProdUniqueId;

	params[":eventName"] = eventName;
	params[":deviceId"] = deviceId;

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
	json_spirit::mValue request_data;
#elif defined(COM_SUPPORT_LIB_POCO)
	Poco::JSON::Object request_data;
#endif
	std::string http_return_data;
	this->internals_->httpRequest("GET", "permission/events/:eventName/rights/:deviceId", params, queries, request_data, http_return_data);
	this->internals_->parseCheckEffectivePermissionRight(data, http_return_data);
}

// API Method: Check Effective Permission Events
void ctn::CtnApiClient::retrieveDeviceIdInfo(DeviceIdInfoResult &data, std::string deviceId, std::string isProdUniqueId = "false")
{

	std::map<std::string, std::string> params;
	std::map<std::string, std::string> queries;

	queries["isProdUniqueId"] = isProdUniqueId;

	params[":deviceId"] = deviceId;

#if defined(COM_SUPPORT_LIB_BOOST_ASIO)
	json_spirit::mValue request_data;
#elif defined(COM_SUPPORT_LIB_POCO)
	Poco::JSON::Object request_data;
#endif
	std::string http_return_data;
	this->internals_->httpRequest("GET", "devices/:deviceId", params, queries, request_data, http_return_data);
	this->internals_->parseRetrieveDeviceIdInfo(data, http_return_data);
}

// CtnApiClient Constructor
ctn::CtnApiClient::CtnApiClient(std::string device_id, std::string api_access_secret, std::string host, std::string port, std::string environment, bool secure, std::string version)
{
    // Init internals and pass param
    this->internals_ = new ctn::CtnApiInternals(device_id, api_access_secret, host, port, environment, secure, version);
}

// CtnApiClient Destructor
ctn::CtnApiClient::~CtnApiClient()
{
    delete this->internals_;
}
