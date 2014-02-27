package com.androidhive.pushnotifications;

import static com.androidhive.pushnotifications.CommonUtilities.SENDER_ID;
import static com.androidhive.pushnotifications.CommonUtilities.SERVER_URL;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class RegisterActivity extends Activity {
	// alert dialog manager
	AlertDialogManager alert = new AlertDialogManager();
	
	// Internet detector
	ConnectionDetector cd;
	
	// UI elements
	EditText txtUserName;
	EditText txtPassword;
	EditText txtDeviceId;
	
	// Register button
	Button btnRegister;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_register);
		
		cd = new ConnectionDetector(getApplicationContext());

		// Check if Internet present
		if (!cd.isConnectingToInternet()) {
			// Internet Connection is not present
			alert.showAlertDialog(RegisterActivity.this,
					"Internet Connection Error",
					"Please connect to working Internet connection", false);
			// stop executing code by return
			return;
		}

		// Check if GCM configuration is set
		if (SERVER_URL == null || SENDER_ID == null || SERVER_URL.length() == 0
				|| SENDER_ID.length() == 0) {
			// GCM sernder id / server url is missing
			alert.showAlertDialog(RegisterActivity.this, "Configuration Error!",
					"Please set your Server URL and GCM Sender ID", false);
			// stop executing code by return
			 return;
		}
		
		txtUserName = (EditText) findViewById(R.id.txtUserName);
		txtPassword = (EditText) findViewById(R.id.txtPassword);
		txtDeviceId = (EditText) findViewById(R.id.txtDeviceId);
		btnRegister = (Button) findViewById(R.id.btnRegister);
		
		/*
		 * Click event on Register button
		 * */
		btnRegister.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				// Read EditText dat
				String userName = txtUserName.getText().toString();
				String password = txtPassword.getText().toString();
				String deviceId = txtDeviceId.getText().toString();
				
				// Check if user filled the form
				if(userName.trim().length() > 0 && password.trim().length() > 0 && deviceId.trim().length() > 0){
					// Launch Main Activity
					Intent i = new Intent(getApplicationContext(), MainActivity.class);
					
					// Registering user on our server					
					// Sending registraiton details to MainActivity
					i.putExtra("userName", userName);
					i.putExtra("password", password);
					i.putExtra("deviceId", deviceId);
					startActivity(i);
					finish();
				}else{
					// user doen't filled that data
					// ask him to fill the form
					alert.showAlertDialog(RegisterActivity.this, "Registration Error!", "Please enter your details", false);
				}
			}
		});
	}

}
