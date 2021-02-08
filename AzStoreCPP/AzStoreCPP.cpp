/* 
    Author: Brandon George - dataprimes@gmail.com - 02/2021

    This code is represented "AS-IS" without any warranty or quality implied. 
    Use as you see fit, under no license terms. Including, but not limited to:
    Opensource, Public, Private, Reference, etc. usages.

    About: This code is an example showcase for working with Azure Storage Queue's 
    from C++. This uses the Azure storage client library for C++ 
    (https://github.com/Azure/azure-storage-cpp/blob/master/README.md) 
*/

#define _NO_WASTORAGE_API

#include <iostream>
#include <was/storage_account.h>
#include <was/queue.h>

using namespace std;

class qMessage {
    int _deleted;
    string _msg;
    string _id;
    string _qname;
    string _connStr;
    azure::storage::cloud_storage_account _storeAcct;
    azure::storage::cloud_queue_client _qClient;
    azure::storage::cloud_queue_message _qMsg;
    azure::storage::cloud_queue queue _q;
public:
    qMessage(string);
    
    // Peek the next message in the queue:
    string peekMsg() { 
        
        _qMsg = _q.peek_message();
        _msg = _qMsg.content_as_string();
        
        return _msg; 
    }

    //Dequeues message:
    int deleteMsg() { 
        
        _deleted = 1;

        _qMsg = _q.get_message();
        queue.delete_message(_qMsg);
        
        return _deleted; 
    }
};

// Int a new instance of qMessage and connect to storage and specific queue to work with:
qMessage::qMessage(string q) {
    _qname = q;
    _connStr = utility::string_t storage_connection_string(U("UseDevelopmentStorage=true;"));
    _storeAcct = azure::storage::cloud_storage_account::parse(_connStr);
    _qClient = _storeAcct.create_cloud_queue_client();
    _qMsg = queue_client.get_queue_reference(U(q));
}


int main()
{
    // Create a new instance of the class qMessage:
    qMessage qMsg = qMessage::qMessage("wmsorders");

    // Peek the first message in the queue:
    string qMsgText = qMsg.peekMsg();
    std::cout << "Message: " << qMsgText << std::endl;

    // Dequeue / delete first message in the queue:
    qMsg.deleteMsg();
}


