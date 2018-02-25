namespace FaramirAPI.Model
{
    // TODO this will not work when room based temperature is measured
    public enum MeasurementPoint
    {
        Undefined,
        Vent_in,
        Vent_inheated,
        Vent_out,
        Vent_outcooled,
        Room,
        Outside
    }
}
