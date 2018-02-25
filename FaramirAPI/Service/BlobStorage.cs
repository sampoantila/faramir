using System;
using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.Blob;
using Microsoft.Extensions.Configuration;

namespace FaramirAPI.Service
{
    public class BlobStorage
    {
        private readonly CloudBlobContainer logContainer;
        private readonly CloudBlobContainer measurementContainer;
        private CloudBlobClient blobClient;

        public BlobStorage(IConfiguration configuration)
        {
            // Retrieve storage account from connection string.
            CloudStorageAccount storageAccount = CloudStorageAccount.Parse(configuration.GetConnectionString("DefaultConnection"));

            // Create the blob client.
            blobClient = storageAccount.CreateCloudBlobClient();

            // Retrieve a reference to a container.
            logContainer = blobClient.GetContainerReference("log");

            // Retrieve a reference to a container.
            measurementContainer = blobClient.GetContainerReference("measurement");
        }

        public CloudAppendBlob CreateLogBlob()
        {
            return logContainer.GetAppendBlobReference($"log_{DateTime.Now:yyyy-MM-dd_hh:mm:ss.fff}");
        }
        public CloudBlockBlob CreateMeasurementBlob(string prefix)
        {
            return measurementContainer.GetBlockBlobReference($"{prefix}_{DateTime.Now:yyyy-MM-dd_hh:mm:ss.fff}");
        }
    }
}

