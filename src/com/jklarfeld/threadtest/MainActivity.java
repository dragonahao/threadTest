package com.jklarfeld.threadtest;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	static
	{
		System.loadLibrary("threadCreate");
	}
	
	public void createThread(View v)
	{
		long numCores = getNumCores();
		//numCores = 1;
		for (int i=0; i<(int)numCores; i++)
		{
			createThread();
		}
	}
	
	private native long getNumCores();
	private native boolean createThread();
}
