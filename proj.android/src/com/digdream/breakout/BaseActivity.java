package com.digdream.breakout;

import java.util.List;

import com.digdream.test.R;
import com.lenovo.gamesdk.GameShare;
import com.lenovo.gamesdk.GameShare.Bindlistener;
import com.lenovo.game.GameUserInfo;
import com.lenovo.game.GameUserListener;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.DialogInterface.OnKeyListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;

public abstract class BaseActivity extends Activity implements Bindlistener {

	private static final String TAG = "BaseActivity";
	protected static GameShare mGameShare = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		if (mGameShare == null)
			mGameShare = new GameShare(getApplicationContext());
		mGameShare.addUserListener(mUserListener);

		new Thread() {
			@Override
			public void run() {
				mGameShare.bind(BaseActivity.this);
			}
		}.start();
	}

	@Override
	protected void onDestroy() {
		if (mGameShare != null) {
			mGameShare.removeUserListener(mUserListener);
			mGameShare.unbind(BaseActivity.this);
		}
		super.onDestroy();
	}
	
	protected static GameUserInfo getRemoteUser() {
		List<GameUserInfo> users = mGameShare.getRemoteUsers();
		if (users.size() < 1) {
			return null;
		}
		return users.get(0);
	}
	
	//
	private GameUserListener mUserListener = new GameUserListener() {

		@Override
		public void onLocalUserChanged(UserEventType type, GameUserInfo user) {
			Log.v(TAG, "onLocalUserChanged, eventType : " + type
					+ ", userInfo : " + user);
		}

		@Override
		public void onRemoteUserChanged(UserEventType type, GameUserInfo user) {
			switch (type) {
			case OFFLINE:
				Log.d(TAG, "Remote offline " + user.name);
				if (user.id.equals(getRemoteUser().id)) {
					mHandler.sendEmptyMessage(0);
				}
				break;
			default:
				break;
			}
		}
	};
	protected void showOfflineDialog() {
		AlertDialog.Builder builder = new Builder(BaseActivity.this);
		builder.setMessage(R.string.offline);
		builder.setPositiveButton(R.string.ok, new OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				dialog.dismiss();
				BaseActivity.this.finish();
				System.exit(0);
			}
		});
		builder.setOnKeyListener(new OnKeyListener() {

			@Override
			public boolean onKey(DialogInterface dialog, int keyCode,
					KeyEvent event) {
				if (keyCode == KeyEvent.KEYCODE_BACK) {
					return true;
				}
				return false;
			}
		});
		builder.create().show();
	}

	Handler mHandler = new Handler() {

		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case 0:
				showOfflineDialog();
				break;

			default:
				break;
			}
			super.handleMessage(msg);
		}

	};

}
