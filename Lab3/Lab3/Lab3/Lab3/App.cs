using Xamarin.Forms;
using Plugin.Vibrate;
namespace Lab3
{
    public class App : Application
    {
        
        public App()
        {
            MainPage = new Pomodoro();
        }
        
        protected override void OnStart()
        {
            // Handle when your app starts
        }

        protected override void OnSleep()
        {
            // Handle when your app sleeps
        }

        protected override void OnResume()
        {
            // Handle when your app resumes
        }
    }
}

