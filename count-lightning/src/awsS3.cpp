#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <fstream>
#include <aws/s3/model/Object.h>
#include <aws/transfer/TransferHandle.h>
#include <aws/transfer/TransferManager.h>


//bool downLoadObject(Aws::String& KEY, Aws::String& BUCKET, Aws::String& filename) {
//    const Aws::String fileName = "../netcdf/" + filename;
//
//    auto s3_client = Aws::MakeShared<Aws::S3::S3Client>("S3Client");
//    auto executor = Aws::MakeShared<Aws::Utils::Threading::PooledThreadExecutor>("executor", 25);
//    Aws::Transfer::TransferManagerConfiguration transfer_config(executor.get());
//    transfer_config.s3Client = s3_client;
//    auto transfer_manager = Aws::Transfer::TransferManager::Create(transfer_config);
//
//    // Create buffer to hold data received by the data stream. 
//
//    auto creationFunction = [&]() { return Aws::New< Aws::OFStream >("DownloadTag", fileName, std::ofstream::out); };
//    auto downloadHandle = transfer_manager->DownloadFile(BUCKET, KEY, creationFunction);
//    downloadHandle->WaitUntilFinished();// Block calling thread until download is complete.
//    auto downStat = downloadHandle->GetStatus();
//}

bool GetObject(const Aws::String& objectKey,
    const Aws::String& fromBucket,
    const Aws::Client::ClientConfiguration& clientConfig) {
    Aws::S3::S3Client client(clientConfig);

    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(fromBucket);
    request.SetKey(objectKey);

    Aws::S3::Model::GetObjectOutcome outcome =
        client.GetObject(request);

    if (!outcome.IsSuccess()) {
        const Aws::S3::S3Error& err = outcome.GetError();
        std::cerr << "Error: GetObject: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
    }
    else {
        std::cout << "Successfully retrieved '" << objectKey << "' from '"
            << fromBucket << "'." << std::endl;
    }

    return outcome.IsSuccess();
}

bool findObject(const Aws::String& bucketName, const Aws::String &subfolder, const Aws::String &date, 
    const Aws::Client::ClientConfiguration& clientConfig) {
    Aws::S3::S3Client s3_client(clientConfig);

    Aws::S3::Model::ListObjectsRequest request;
    request.WithBucket(bucketName).WithPrefix(subfolder);

    auto outcome = s3_client.ListObjects(request);

    if (!outcome.IsSuccess()) {
        std::cerr << "Error: ListObjects: " <<
            outcome.GetError().GetMessage() << std::endl;
    }
    else {
        Aws::Vector<Aws::S3::Model::Object> objects =
            outcome.GetResult().GetContents();

        for (Aws::S3::Model::Object& object : objects) {
            std::string fileSubstringAtS3 = object.GetKey().substr(44, 14); // a file substring representing the netcdf start scan
            if (fileSubstringAtS3 == date) {
                Aws::String objectKey = object.GetKey();
                std::cout << "Retrieving " << fileSubstringAtS3 << " from S3" << std::endl;
                GetObject(objectKey, bucketName, clientConfig);
                break;
            }
        }
    }
    return outcome.IsSuccess();
}

