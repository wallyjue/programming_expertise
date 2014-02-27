package com.androidhive.pushnotifications;

import static com.androidhive.pushnotifications.CommonUtilities.APP_ID;
import static com.androidhive.pushnotifications.CommonUtilities.APP_SECRET;
import static com.androidhive.pushnotifications.CommonUtilities.SERVER_URL;
import static com.androidhive.pushnotifications.CommonUtilities.TAG;
import static com.androidhive.pushnotifications.CommonUtilities.displayMessage;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicHeader;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.protocol.HTTP;
import org.apache.http.util.EntityUtils;
import org.json.JSONObject;

import android.content.Context;
import android.util.Log;

import com.google.android.gcm.GCMRegistrar;

public final class ServerUtilities {
	private static final int MAX_ATTEMPTS = 5;
	private static final int BACKOFF_MILLI_SECONDS = 2000;
	private static final Random random = new Random();

	/**
	 * Register this account/device pair within the server.
	 * 
	 */
	static void register(final Context context, String userName,
			String password, String deviceId, final String regId) {
		Log.i(TAG, "registering device (regId = " + regId + ")");

		long backoff = BACKOFF_MILLI_SECONDS + random.nextInt(1000);
		// Once GCM returns a registration id, we need to register on our server
		// As the server might be down, we will retry it a couple
		// times.
		for (int i = 1; i <= MAX_ATTEMPTS; i++) {
			Log.d(TAG, "Attempt #" + i + " to register");
			try {
				displayMessage(context, context.getString(
						R.string.server_registering, i, MAX_ATTEMPTS));

				String token = authenticate(userName, password);
				register(regId, token, deviceId);

				GCMRegistrar.setRegisteredOnServer(context, true);
				String message = context.getString(R.string.server_registered);
				CommonUtilities.displayMessage(context, message);
				return;
			} catch (Exception e) {
				// Here we are simplifying and retrying on any error; in a real
				// application, it should retry only on unrecoverable errors
				// (like HTTP error code 503).
				Log.e(TAG, "Failed to register on attempt " + i, e);
				if (i == MAX_ATTEMPTS) {
					break;
				}
				try {
					Log.d(TAG, "Sleeping for " + backoff + " ms before retry");
					Thread.sleep(backoff);
				} catch (InterruptedException e1) {
					// Activity finished before we complete - exit.
					Log.d(TAG, "Thread interrupted: abort remaining retries!");
					Thread.currentThread().interrupt();
					return;
				}
				// increase backoff exponentially
				backoff *= 2;
			}
		}
		String message = context.getString(R.string.server_register_error,
				MAX_ATTEMPTS);
		CommonUtilities.displayMessage(context, message);
	}

	/**
	 * Unregister this account/device pair within the server.
	 */
	static void unregister(final Context context, final String regId) {
		// Log.i(TAG, "unregistering device (regId = " + regId + ")");
		// String serverUrl = SERVER_URL + "/unregister";
		// Map<String, String> params = new HashMap<String, String>();
		// params.put("regId", regId);
		// try {
		// post(serverUrl, params);
		// GCMRegistrar.setRegisteredOnServer(context, false);
		// String message = context.getString(R.string.server_unregistered);
		// CommonUtilities.displayMessage(context, message);
		// } catch (IOException e) {
		// // At this point the device is unregistered from GCM, but still
		// // registered in the server.
		// // We could try to unregister again, but it is not necessary:
		// // if the server tries to send a message to the device, it will get
		// // a "NotRegistered" error message and should unregister the device.
		// String message = context.getString(
		// R.string.server_unregister_error, e.getMessage());
		// CommonUtilities.displayMessage(context, message);
		// }
	}

	private static String authenticate(String userName, String password)
			throws Exception {
		String serverUrl = SERVER_URL + "/oauth/token";
		Log.i(TAG, "auth by " + serverUrl);
		
		HttpClient client = new DefaultHttpClient();
		HttpPost post = new HttpPost(serverUrl);

		List<NameValuePair> pairs = new ArrayList<NameValuePair>();
		pairs.add(new BasicNameValuePair("grant_type", "password"));
		pairs.add(new BasicNameValuePair("client_id", APP_ID));
		pairs.add(new BasicNameValuePair("client_secret", APP_SECRET));
		pairs.add(new BasicNameValuePair("username", userName));
		pairs.add(new BasicNameValuePair("password", password));
		post.setEntity(new UrlEncodedFormEntity(pairs));
		
		HttpResponse response = client.execute(post);
		String result = EntityUtils.toString(response.getEntity());
		JSONObject jObject = new JSONObject(result);
		
		Log.i(TAG, "get auth response : " + jObject);
		
		return jObject.getString("access_token");
	}

	/**
	 * Issue a POST request to the server.
	 * 
	 * @param endpoint
	 *            POST address.
	 * @param params
	 *            request parameters.
	 * 
	 * @throws IOException
	 *             propagated from POST.
	 */
	private static void register(String regId, String token, String deviceId)
			throws Exception {
		String serverUrl = SERVER_URL + "/v1.1/device/" + deviceId + "/mobile";
		DefaultHttpClient httpclient = new DefaultHttpClient(
				new BasicHttpParams());
		HttpPost post = new HttpPost(serverUrl);

		int imei = (int) (Math.random() * 100000);
		JSONObject json = new JSONObject();
		json.put("reg_id", regId);
		json.put("name", String.valueOf(imei));
		json.put("mobile_type", "HTC One X");
		json.put("os_type", "android");
		json.put("os_version", "2.3");
		json.put("imei", String.valueOf(imei));
		json.put("app_id", APP_ID);
		json.put("app_version", "1.1");

		StringEntity se = new StringEntity(json.toString());
		se.setContentType(new BasicHeader(HTTP.CONTENT_TYPE, "application/json"));
		se.setContentType(new BasicHeader("Authorization", "Bearer " + token));
		post.setEntity(se);
		
		HttpResponse response = httpclient.execute(post);
		String result = EntityUtils.toString(response.getEntity());
		JSONObject jObject = new JSONObject(result);
		
		Log.i(TAG, "get register mobile device response : " + jObject);
	}
}
