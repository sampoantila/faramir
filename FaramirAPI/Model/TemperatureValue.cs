using System;

namespace FaramirAPI.Model
{
    [Serializable]
    public class TemperatureValue
    {
        public decimal Value { get; set; }
        public DateTime TimeStamp { get; set; }
        public MeasurementPoint Point { get; set; }
    }
}