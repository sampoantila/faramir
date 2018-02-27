using System;
using System.Collections.Generic;
using FaramirAPI.Model;
using FaramirAPI.Service;
using Microsoft.AspNetCore.Mvc;

namespace FaramirAPI.Controllers
{
    [Produces("application/json")]
    [Route("api/Temp")]
    public class TempController : Controller
    {
        public BlobStorage Storage { get; private set; }

        public TempController(BlobStorage storage)
        {
            Storage = storage;
        }

        // GET: api/Temp
        [HttpGet]
        public IEnumerable<string> Get()
        {
            return new string[] { "value1", "value2" };
        }

        // GET: api/Temp/5
        [HttpGet("{id}", Name = "Get")]
        public string Get(int id)
        {
            return "value";
        }
        
        // POST: api/Temp
        [HttpPost]
        public void Post(string value, int point)
        {
            var blob = Storage.CreateMeasurementBlob("temp");

            var entity = new TemperatureValue
            {
                Point = (MeasurementPoint)point,
                TimeStamp = DateTime.Now,
                Value = decimal.Parse(value)
            };

            blob.UploadTextAsync(entity.SerializeObject());
        }
        
        //// PUT: api/Temp/5
        //[HttpPut("{id}")]
        //public void Put(int id, [FromBody]string value)
        //{
        //}
        
        //// DELETE: api/ApiWithActions/5
        //[HttpDelete("{id}")]
        //public void Delete(int id)
        //{
        //}
    }
}
