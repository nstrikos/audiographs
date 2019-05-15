package org.nstrikos.access.audiographs;

import org.qtproject.qt5.android.bindings.QtActivity;
import org.qtproject.qt5.android.bindings.QtApplication;
import android.util.Log;
import android.content.Context;
import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.os.Vibrator;

import android.os.Build;
import android.os.VibrationEffect;

public class AndroidClient extends QtActivity implements TextToSpeech.OnInitListener
{

    private static AndroidClient m_instance;
    private static  TextToSpeech tts;
    public static Vibrator m_vibrator;

    public AndroidClient()
    {
        System.out.println("Java constructor " );
        m_instance = this;
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            tts = new TextToSpeech(this,this);
    }

    public void onInit(int status) {

    }

    @Override
    protected void onDestroy() {
            super.onDestroy();
            tts.shutdown();
    }

    public static void speak(String msg)
    {
        System.out.println(msg );
        tts.speak(msg, TextToSpeech.QUEUE_FLUSH, null);
    }

    public static void vibrate(String msg)
    {
        if (m_vibrator == null)
        {
            System.out.println("null vibrator");

            if (m_instance != null)
            {
                System.out.println("setting vibrator");
                m_vibrator = (Vibrator) m_instance.getSystemService(Context.VIBRATOR_SERVICE);

                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                    m_vibrator.vibrate(VibrationEffect.createOneShot(500, VibrationEffect.DEFAULT_AMPLITUDE));
                } else {
                    //deprecated in API 26
                    m_vibrator.vibrate(500);
                }
            }
        }
        else m_vibrator.vibrate(5000);
    }
}
