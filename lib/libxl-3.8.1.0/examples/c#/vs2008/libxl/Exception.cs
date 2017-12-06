namespace libxl
{
    public class Exception : System.Exception
    {
        public Exception(string message)
            : base("libxl: " + message)
        {
        }
    }
}
