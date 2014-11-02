package com.digdream.breakout;

import org.json.JSONException;

import com.digdream.breakout.module.GameData;
import com.digdream.breakout.module.GameMessages;
import com.digdream.breakout.module.GameMessages.AbstractGameMessage;
import com.digdream.breakout.module.GameMessages.GameDataMessage;
import com.lenovo.game.GameMessage;
import com.lenovo.game.GameMessageListener;
import com.lenovo.game.GameUserInfo;
import com.lenovo.gamesdk.GameShare.Bindlistener;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

public class MainActivity extends BaseActivity implements Bindlistener {

	private static final String TAG = "MainActivity";
	private GameData mGameData = null;
	public static int gameMode = 1;

	@Override
	public void onBind(boolean arg0) {
		Log.v(TAG, "onBind(), success : " + arg0);
		if (!arg0) {
			Toast.makeText(getApplicationContext(), "Bind Service failed.",
					Toast.LENGTH_LONG).show();
			return;
		}
		mGameShare.addMessageListener(mMessageListener);
	}

	@Override
	protected void onDestroy() {
		if (mGameShare != null)
			mGameShare.removeMessageListener(mMessageListener);
		super.onDestroy();
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		init();
		MainActivity.mContext = this;
		toNextActivity();
		mGameShare.addMessageListener(mMessageListener);
	}

	private GameMessageListener mMessageListener = new GameMessageListener() {

		@Override
		public void onMessage(GameMessage gameMessage) {
			Log.v(TAG, "onMessage, message : " + gameMessage.toString());
			Toast.makeText(getApplicationContext(), gameMessage.toString(),
					Toast.LENGTH_SHORT).show();
			AbstractGameMessage msg;
			try {
				msg = GameMessages.createGameMessage(gameMessage.getType(),
						gameMessage.getMessage());
				msg.setFrom(gameMessage.getFrom());
				msg.setTo(gameMessage.getTo());
			} catch (JSONException e) {
				Log.d(TAG, "json error!");
				return;
			}
			if (msg.getType().equalsIgnoreCase(GameMessages.MSG_TYPE_GAME_DATA)) {
				GameDataMessage dataMsg = (GameDataMessage) msg;
				String gameData = dataMsg.getGameData();
				mGameData.generateGameData(gameData);
			} else if (msg.getType().equalsIgnoreCase(
					GameMessages.MSG_TYPE_GAME_PREPARED)) {
				mGameData.mIsRemotePrepared = true;
			} else if (msg.getType().equalsIgnoreCase(
					GameMessages.MSG_TYPE_GAME_BEGIN)) {
				if (!mGameData.mIsInviter) {

				}
			}
		}
	};

	private void toNextActivity() {
		// initMode();
		Intent intent = new Intent();
		intent.setClass(MainActivity.this, AppActivity.class);
		startActivity(intent);
	}

	private void init() {
		Intent intent = getIntent();
		int mode = 1;
		boolean isInviter = false;
		if (intent.hasExtra("mode")) {
			mode = intent.getIntExtra("mode", 1);
			gameMode = intent.getIntExtra("mode", 1);
		}
		Log.v(TAG, "game mode : " + mode);
		if (intent.hasExtra("inviter"))
			isInviter = intent.getBooleanExtra("inviter", false);
		Log.v(TAG, "is inviter : " + isInviter);

		mGameData = GameData.createGameData(mode, isInviter);
		if (mode == 1 || isInviter)
			mGameData.generateGameData(GameData.BLOCK_ROW_COUNT,
					GameData.BLOCK_COLUMN_COUNT);

	}

	private native void initMode();

	private static native boolean isInviter();

	private static void initStatic() {
		Log.w(TAG, "initStatic");
	}

	/*
	 * sendPreparedMessage 发送已准备好的Message 内容：
	 */
	public static void sendPreparedMessage(int level) {
		GameUserInfo localUser = mGameShare.getLocalUser();

		GameUserInfo remoteUser = getRemoteUser();
		Log.w(TAG, "hhh" + "  " + gameMode);
		/*
		 * if (localUser == null || remoteUser == null) { Log.w(TAG,
		 * "localUser == null || remoteUser == null" + gameMode); return; }
		 */
		GameDataMessage dataMsg = new GameDataMessage(localUser.id,
				"remoteUser.id", GameData.array2String(level));
		GameMessage msg = dataMsg.toGameMessage();
		if (msg == null) {
			Log.w(TAG, "msg == null" + gameMode);
			return;
		}

		mGameShare.sendMessage(msg);
		Log.w(TAG, msg.getMessage());
	}

	/*
	 * initToast 展示toast调用
	 * 
	 * @param String str toast信息。
	 */
	public static void initToast(String str) {
		Message msg = new Message();
		msg.what = 1;
		msg.obj = str;
		Statichandler.sendMessage(msg);
	}

	public static Activity mContext;
	static Handler Statichandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case 1:
				String StrMsg = (String) msg.obj;
				Toast.makeText(mContext, StrMsg, Toast.LENGTH_SHORT).show();
				break;
			default:
				break;
			}
		};
	};

	/*
	 * initGameMode 调用此函数，得到游戏的人数 调用
	 */
	private static int initGameMode() {
		return gameMode;
	}
}
