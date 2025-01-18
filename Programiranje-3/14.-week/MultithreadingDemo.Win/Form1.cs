using System.Diagnostics;

namespace MultithreadingDemo.Win
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private async void btnDownload_Click(object sender, EventArgs e)
        {
            Debug.WriteLine($"From button handler {Thread.CurrentThread.ManagedThreadId}");
            var result = "";
            await Task.Run(async () =>
            {
                var client = new HttpClient();
                result = await client.GetStringAsync("https://www.unmo.ba");
            });

            var context = SynchronizationContext.Current;
            await Task.Run(() =>
            {
                for (int i = 0; i < result.Length; i++)
                {
                    Thread.Sleep(100);
                    context.Post(delegate { rtResult.Text += result[i]; }, null);
                    //rtResult.Invoke(() =>
                    //{
                    //    Debug.WriteLine($"From within invoke {Thread.CurrentThread.ManagedThreadId}");
                    //    rtResult.Text += result[i];
                    //});
                }
            });
        }

        //int i = 0;
        //private void btnSimulateMultiAccess_Click(object sender, EventArgs e) // This is bad idea happening :S
        //{
        //    var context = SynchronizationContext.Current;

        //    new Thread(() => { i++; context.Post(delegate { rtResult.Text += $"First thread {i}\n"; }, null); }).Start();
        //    new Thread(() => { i++; context.Post(delegate { rtResult.Text += $"Second thread {i}\n"; }, null); }).Start();
        //}

        int i = 0;
        object Locker  = new object();
        SynchronizationContext context;

        private void btnSimulateMultiAccess_Click(object sender, EventArgs e)
        {
            context = SynchronizationContext.Current;
            new Thread(ActualWorkV2).Start();
            new Thread(ActualWorkV2).Start();
        }

        private void ActualWork()
        {
            lock(Locker)
            {
                i++; 
                context.Send(delegate { rtResult.Text += $"{i}\n"; }, null);
            }
        }

        private void ActualWorkV2()
        {
            Monitor.Enter(Locker);
            i++;
            context.Send(delegate { rtResult.Text += $"{i}\n"; }, null);
            Monitor.Exit(Locker);
        }

        private void ActualWorkV3()
        {
            try
            {
                Monitor.Enter(Locker);
                i++;
                context.Send(delegate { rtResult.Text += $"{i}\n"; }, null);
            }
            catch (Exception ex) { }
            finally { Monitor.Exit(Locker); }
        }
    }
}
