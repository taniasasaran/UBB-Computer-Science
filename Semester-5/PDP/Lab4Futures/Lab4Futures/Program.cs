using System.Data;
using System.Diagnostics;
using Lab4Futures.Implementation;

namespace Lab4Futures;

public class Program
{
    static void Main()
    {
        Stopwatch stopwatch = new Stopwatch();
        var hosts = new List<string>
        {
            //"www.tu-si-cu-mi-ne.ro/",
            //"www.catena.ro/beres-vitamina-c-1000-mg-x-30-comprimate"  // content moved
            //"international.au.dk/"  // content moved
            //"www.imperial.ac.uk" // content moved
            "www.columbia.edu/~fdc/sample.html",
            //"www.cs.ubbcluj.ro/~rlupsa/edu/pdp/index.html"  // content moved
        };

        Console.WriteLine("-----DIRECT CALLBACK-----");
        stopwatch.Start();
        DirectCallback.Run(hosts);
        stopwatch.Stop();
        TimeSpan directCallbackTime = stopwatch.Elapsed;

        Thread.Sleep(3000);

        Console.WriteLine("\n-----TASKS-----");
        stopwatch.Restart();
        TaskMechanism.Run(hosts);
        stopwatch.Stop();
        TimeSpan taskMechanismTime = stopwatch.Elapsed;

        Thread.Sleep(3000);

        Console.WriteLine("\n-----ASYNC/AWAIT TASKS-----");
        stopwatch.Restart();
        AsyncTaskMechanism.Run(hosts);
        stopwatch.Stop();
        TimeSpan asyncTaskMechanismTime = stopwatch.Elapsed;

        Console.WriteLine("Direct callback: {0}", directCallbackTime);
        Console.WriteLine("Task mechanism: {0}", taskMechanismTime);
        Console.WriteLine("Async task mechanism: {0}", asyncTaskMechanismTime);
    }
}
