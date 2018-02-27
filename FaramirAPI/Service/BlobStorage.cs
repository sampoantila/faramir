using System;
using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.Blob;
using Microsoft.Extensions.Configuration;

namespace FaramirAPI.Service
{
    public class BlobStorage
    {
        private readonly string connectionString;

        public BlobStorage(IConfiguration configuration)
        {
            connectionString = configuration.GetConnectionString("measurement");
        }

        public CloudAppendBlob CreateLogBlob()
        {
            return CreateLogContainer().GetAppendBlobReference($"log_{DateTime.Now:yyyy-MM-dd_hh:mm:ss.fff}");
        }
        public CloudBlockBlob CreateMeasurementBlob(string prefix)
        {
            return CreateMeasurementContainer().GetBlockBlobReference($"{prefix}_{DateTime.Now:yyyy-MM-dd_hh:mm:ss.fff}");
        }

        private CloudBlobContainer CreateLogContainer()
        {
            var client = CreateBlobClient();

            // Retrieve a reference to a container.
            return client.GetContainerReference("log");
        }

        private CloudBlobClient CreateBlobClient()
        {
            // Retrieve storage account from connection string.
            CloudStorageAccount storageAccount = CloudStorageAccount.Parse(connectionString);

            // Create the blob client.
            return storageAccount.CreateCloudBlobClient();
        }

        private CloudBlobContainer CreateMeasurementContainer()
        {
            var client = CreateBlobClient();

            // Retrieve a reference to a container.
            return client.GetContainerReference("measurement");
        }
    }
}

