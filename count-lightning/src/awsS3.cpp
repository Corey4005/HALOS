#include <aws/s3/model/Object.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "awsS3.h"
/*
 * This module contains functions for interacting with Amazon S3 storage.
 * It includes functions for finding and downloading objects from a bucket.
 */

int downLoadCount = 1; //a variable to count the number of downloads 
bool GetObject(const Aws::String& objectKey,
    const Aws::String& fromBucket, const Aws::String& date,
    const Aws::Client::ClientConfiguration& clientConfig) {
    // Create an S3 client using the provided client configuration
    Aws::S3::S3Client client(clientConfig);

    // Set up the request to download the object from the specified bucket
    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(fromBucket);
    request.SetKey(objectKey);

    // Download the object and check for errors
    Aws::S3::Model::GetObjectOutcome outcome = client.GetObject(request);
    if (!outcome.IsSuccess()) {
        // Print an error message if the download failed
        const Aws::S3::S3Error& err = outcome.GetError();
        std::cerr << "Error: GetObject: " << err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
    }
    else {
        // If the download was successful, create the filename and save the object to a local file
        std::string filename = "\\netcdf\\" + date + ".nc";
        std::filesystem::path cwd = std::filesystem::current_path();
        std::string local_file_name = cwd.string() + filename;
        std::ofstream localfile(local_file_name, std::ios::out | std::ios::binary);
        auto& retrieved = outcome.GetResult().GetBody();
        localfile << retrieved.rdbuf();
    }
    //return if outcome request successful
    return outcome.IsSuccess();
}


bool findObject(const Aws::String& bucketName,
    const Aws::String& subfolder,
    const Aws::String& date,
    const Aws::Client::ClientConfiguration& client, 
    bool downloadObject, int&batchNumberCount, int& nPointsCount) {
    // Create an S3 client using the provided client configuration
    Aws::S3::S3Client s3_client(client);

    // Set up the request to list objects in the specified bucket with the specified prefix
    Aws::S3::Model::ListObjectsRequest request;
    request.WithBucket(bucketName).WithPrefix(subfolder);

    // List the objects in the bucket and check for errors
    auto outcome = s3_client.ListObjects(request);
    if (!outcome.IsSuccess()) {
        // Print an error message if the request failed
        std::cerr << "Error: ListObjects: " << outcome.GetError().GetMessage() << std::endl;
    }

    //if downloadObject is true, iterate through the objects for each date and download file
    if (downloadObject == true) {
        Aws::Vector<Aws::S3::Model::Object> objects = outcome.GetResult().GetContents();
        for (Aws::S3::Model::Object& object : objects) {
            // Extract the file substring representing the netcdf start scan
            std::string fileSubstringAtS3 = object.GetKey().substr(44, 14);
            if (fileSubstringAtS3 == date) {
                // If the file substring matches the specified date, download it by calling getObject
                Aws::String objectKey = object.GetKey();
                std::cout << "Downloading " << date << " from s3!" << " Total Downloads Count: " << downLoadCount << " This Batch Count: " << batchNumberCount << "/" << nPointsCount << std::endl;
                downLoadCount++; 
                GetObject(objectKey, bucketName, date, client);

            }
        }
    }
    else if (downloadObject == false) {
        // If downloadObject is false, iterate through the objects in the bucket
        Aws::Vector<Aws::S3::Model::Object> objects = outcome.GetResult().GetContents();
        for (Aws::S3::Model::Object& object : objects) {
            // Extract the file substring representing the netcdf start scan
            std::string fileSubstringAtS3 = object.GetKey().substr(44, 14);
            if (fileSubstringAtS3 == date) {
                // If the file substring matches the specified date, print a message indicating that the object exists in the bucket
                Aws::String objectKey = object.GetKey();
                std::cout << fileSubstringAtS3 << " exists " << "at s3 bucket: " << objectKey << std::endl;
            }
        }

 
    }
    // Return whether the request was successful
    return outcome.IsSuccess();
}