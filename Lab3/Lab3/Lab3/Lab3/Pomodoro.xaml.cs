using System;
using Xamarin.Forms;
using AdvancedTimer.Forms.Plugin.Abstractions;
using Plugin.Vibrate;
namespace Lab3
{

    public partial class Pomodoro : ContentPage
    {

        static IAdvancedTimer timer = DependencyService.Get<IAdvancedTimer>();
        int timerTime;
        bool timerFlag = true; // true - runs, false - paused
        int phase = 0,rounds = 4; //phase: work/rest /work/rest /work/rest/ work/relax (0-7) ; round->[work+rest]

        public Pomodoro()
        {
            InitializeComponent();
        }
        
        private void SetTimer(int i)
        {
            switch (i)
            {
                case 0://"Begin cycles":
                    CrossVibrate.Current.Vibration(1000);
                    State.Text = "State: [25 min] Working!";
                    onStart();
                    TimerState();
                    break;
                case 1://"pause"
                    StartButton.Text = "Resume";
                    timer.stopTimer();
                    timerFlag = false;
                    TimerState();
                    break;
                case 2://"resume":
                    StartButton.Text = "Pause";
                    timer.startTimer();
                    timerFlag = true;
                    TimerState();
                    break;

                case 3:// "work":
                    CrossVibrate.Current.Vibration(1000);
                    TimeLeft.Text = "25:00";
                    timerTime = 25 * 60 * 1000;
                    State.Text = "State: [25 min] Working.";
                    TimerState();
                    break;

                case 4:// "rest":
                    CrossVibrate.Current.Vibration(1000);
                    TimeLeft.Text = "5:00";
                    timerTime = 5 * 60 * 1000;
                    State.Text = "State: [5 min] Resting.";
                    TimerState();
                    break;

                case 5:// "relax":
                    CrossVibrate.Current.Vibration(1000);
                    TimeLeft.Text = "35:00";
                    timerTime = 35 * 60 * 1000;
                    State.Text = "State: [35 min] Relaxing";
                    TimerState();
                    break;
            }
            return;
        }

        private async void HelpButton_OnClicked(object sender, EventArgs e)
        {
            await DisplayAlert("Instructions", "The concept is simple: \r\n1) Work hard on your task 25 mins. \r\n2) Rest 5 mins. \r\n3) Repeat steps 1-2 max 4 times. \r\n4) Rest 30 mins and return to step 1. \r\nYou may repeat this as much as you like. \r\nEffectiveness is guaranteed!", "Okay, thanks!");
        }

        private void ResetButton_OnClicked(object sender, EventArgs e)
        {
            onReset();
        }

        private void SkipButton_OnClicked(object sender, EventArgs e)
        {
            onSkip();
        }

        int i = 0; // state 0: begin , state 1-2: pause/resume
        private void StartButton_OnClicked(object sender, EventArgs e)
        {
            SetTimer(i); //start at 0 once
            i += 1;
            if (i > 2) { i = 1; } // then alter between 1 - 2
        }

        
        public void onTick(int millisUntilFinished)
        {
            int seconds = (int)((millisUntilFinished / 1000) % 60);
            int minutes = (int)((millisUntilFinished / (1000 * 60)) % 60);
            
            TimeLeft.Text = String.Format(minutes.ToString("D2")+":"+seconds.ToString("D2"));
        }
        public bool TimerState()
        {
            if (timerFlag) { TimerStates.Text = "Timer State: Running!"; }
            else { TimerStates.Text = "Timer State: Paused"; }

            return true;
        }

        public bool onFinish()
        {
            TimeLeft.Text = "00:00";
            State.Text = "State: Done!";
            timer.stopTimer();
            timerFlag = false;
            TimerState();
            CrossVibrate.Current.Vibration(1000);
            return true;
        }
        public bool onReset()
        {
            StartButton.Text = "Start Effectiveness";
            rounds = 4;
            timerFlag = false;
            TimeLeft.Text = "25:00";
            State.Text = "State: -";
            i = 0;
            return true;
        }

        public bool onSkip()
        {
            timerTime = 0;
            return true;
        }
        public bool onStart()
        {
            timerTime = 25*60*1000;
            StartButton.Text = "Pause";
            rounds = 4;
            timer.initTimer(1000, timerElapsed, false);
            timerFlag = true;
            timer.startTimer();
            phase = 1; // select next phase to be resting
            return true;
        }
        public void timerElapsed(object o, EventArgs e)
        {
            Device.BeginInvokeOnMainThread(() =>  // this function is called each second
            {
                if (timerFlag)
                {
                    timer.setInterval(timer.getInterval());
                    timerTime -= 1000; //-1s per second
                    if (timerTime < 0) // what to do when timer reaches 00:00
                    {
                       
                            if (phase % 2 == 0) //each even phase is a working phase
                            {
                                SetTimer(3); 
                                rounds -= 1;
                            }
                            else //odd phase = rest phase
                            {
                                if (phase == 7) { SetTimer(5); } // last phase is a relaxation phase 
                                else SetTimer(4);                // otherwise, 5 min rest
                            } 
                        

                        if (phase > 7)
                        { phase = 0; }
                        else
                        { phase += 1; }

                        if (rounds == 0)
                        {
                            onReset();
                        }
                    }
                    else
                    {
                        onTick(timerTime);
                    }
                }
                
            });
        }
    }


}


    

            
        