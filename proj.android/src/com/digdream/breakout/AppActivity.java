/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.digdream.breakout;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;

import com.digdream.breakout.module.GameData;
import com.digdream.breakout.module.GameMessages;
import com.digdream.breakout.module.GameMessages.AbstractGameMessage;
import com.digdream.breakout.module.GameMessages.GameDataMessage;
import com.lenovo.game.GameMessage;
import com.lenovo.game.GameMessageListener;
import com.lenovo.gamesdk.GameShare.Bindlistener;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

public class AppActivity extends Cocos2dxActivity implements Bindlistener {

	private static final String TAG = "AppActivity";
	public static Activity mContext;
	private GameData mGameData = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AppActivity.mContext = this;
		BaseActivity.mGameShare.addMessageListener(mMessageListener);
	}

	@Override
	protected void onDestroy() {
		if (BaseActivity.mGameShare != null)
			BaseActivity.mGameShare.removeMessageListener(mMessageListener);
		super.onDestroy();
	}

	private GameMessageListener mMessageListener = new GameMessageListener() {

		@Override
		public void onMessage(GameMessage gameMessage) {
			Log.v(TAG, "onMessage, message : " + gameMessage.toString());
			Toast.makeText(getApplicationContext(), gameMessage.toString(),
					Toast.LENGTH_SHORT).show();
			Toast.makeText(getApplicationContext(), "df", Toast.LENGTH_SHORT)
					.show();
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

	@Override
	public void onBind(boolean arg0) {
		BaseActivity.mGameShare.addMessageListener(mMessageListener);
	}
}
