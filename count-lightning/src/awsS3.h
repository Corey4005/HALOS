#ifndef AWSS3
#define AWSS3
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/Object.h> <iostream>

bool ListObjects(const Aws::String& bucketName,
    const Aws::Client::ClientConfiguration& clientConfig);

#endif