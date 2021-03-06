package com.digdream.breakout.module;

import org.json.JSONException;
import org.json.JSONObject;

import com.lenovo.game.GameMessage;

public class GameMessages {
    // Only inviter send this message, as only inviter generate game data and send game data to other users.
    public static final String MSG_TYPE_GAME_DATA = "game_data";
    // User send this message after prepared, but inviter needn't send it.
    public static final String MSG_TYPE_GAME_PREPARED = "game_prepared";
    // Only inviter send this message, when inviter received all user's prepared message, will send it.
    public static final String MSG_TYPE_GAME_BEGIN = "game_begin";
    // All users have to send this message after completed game.
    public static final String MSG_TYPE_GAME_END = "game_end";
    // All users have to send this message after game step is updated.
    public static final String MSG_TYPE_GAME_STEP = "game_step";

    public static abstract class AbstractGameMessage {
        AbstractGameMessage(String type) {
            mType = type;
        }

        public void setFrom(String from) {
            mFrom = from;
        }

        public void setTo(String to) {
            mTo = to;
        }

        public String getFrom() {
            return mFrom;
        }

        public String getTo() {
            return mTo;
        }

        public String getType() {
            return mType;
        }

        public GameMessage toGameMessage() {
            try {
                GameMessage gameMsg = new GameMessage(mType, mFrom, mTo);
                gameMsg.setMessage(toJSON().toString());
                return gameMsg;
            } catch (JSONException e) {}
            return null;
        }

        abstract public JSONObject toJSON() throws JSONException;

        abstract public void fromJSON(JSONObject json) throws JSONException;

        private String mType;
        private String mFrom;
        private String mTo;
    }

    public static class GameDataMessage extends AbstractGameMessage {
        String mData;

        public GameDataMessage() {
            super(MSG_TYPE_GAME_DATA);
        }

        public GameDataMessage(String from, String to, String gameData) {
            super(MSG_TYPE_GAME_DATA);

            setFrom(from);
            setTo(to);
            mData = gameData;
        }

        public String getGameData() {
            return mData;
        }

        public JSONObject toJSON() throws JSONException {
            JSONObject json = new JSONObject();
            json.put("type", getType());
            json.put("data", mData);
            return json;
        }

        public void fromJSON(JSONObject json) throws JSONException {
            mData = json.getString("data");
        }
    }

    public static class GamePreparedMessage extends AbstractGameMessage {
        public GamePreparedMessage() {
            super(MSG_TYPE_GAME_PREPARED);
        }

        public GamePreparedMessage(String from, String to) {
            super(MSG_TYPE_GAME_PREPARED);
            setFrom(from);
            setTo(to);
        }

        public JSONObject toJSON() throws JSONException {
            JSONObject json = new JSONObject();
            json.put("type", getType());
            return json;
        }

        public void fromJSON(JSONObject json) throws JSONException {}
    }

    public static class GameBeginMessage extends AbstractGameMessage {
        public GameBeginMessage() {
            super(MSG_TYPE_GAME_BEGIN);
        }

        public GameBeginMessage(String from, String to) {
            super(MSG_TYPE_GAME_BEGIN);
            setFrom(from);
            setTo(to);
        }

        public JSONObject toJSON() throws JSONException {
            JSONObject jo = new JSONObject();
            jo.put("type", getType());
            return jo;
        }

        public void fromJSON(JSONObject json) throws JSONException {}
    }

    public static class GameEndMessage extends AbstractGameMessage {
        long mSpentTime;

        public GameEndMessage() {
            super(MSG_TYPE_GAME_END);
        }

        public GameEndMessage(String from, String to, long spentTime) {
            super(MSG_TYPE_GAME_END);
            setFrom(from);
            setTo(to);
            mSpentTime = spentTime;
        }

        public long getSpentTime() {
            return mSpentTime;
        }

        public JSONObject toJSON() throws JSONException {
            JSONObject jo = new JSONObject();
            jo.put("type", getType());
            jo.put("time", mSpentTime);
            return jo;
        }

        public void fromJSON(JSONObject json) throws JSONException {
            mSpentTime = json.getLong("time");
        }
    }

    public static class GameStepMessage extends AbstractGameMessage {
        int mStep;

        public GameStepMessage() {
            super(MSG_TYPE_GAME_STEP);
        }

        public GameStepMessage(String from, String to, int step) {
            super(MSG_TYPE_GAME_STEP);
            setFrom(from);
            setTo(to);

            mStep = step;
        }

        public int getGameStep() {
            return mStep;
        }

        public JSONObject toJSON() throws JSONException {
            JSONObject jo = new JSONObject();
            jo.put("type", getType());
            jo.put("step", mStep);
            return jo;
        }

        public void fromJSON(JSONObject json) throws JSONException {
            mStep = json.getInt("step");
        }
    }

    public static AbstractGameMessage createGameMessage(String type, String message) throws JSONException {
        AbstractGameMessage gameMessage = null;
        JSONObject json = new JSONObject(message);
        if (type.equalsIgnoreCase(MSG_TYPE_GAME_DATA))
            gameMessage = new GameDataMessage();
        else if (type.equalsIgnoreCase(MSG_TYPE_GAME_PREPARED))
            gameMessage = new GamePreparedMessage();
        else if (type.equalsIgnoreCase(MSG_TYPE_GAME_BEGIN))
            gameMessage = new GameBeginMessage();
        else if (type.equalsIgnoreCase(MSG_TYPE_GAME_END))
            gameMessage = new GameEndMessage();
        else if (type.equalsIgnoreCase(MSG_TYPE_GAME_STEP))
            gameMessage = new GameStepMessage();
        if (gameMessage == null)
            return null;

        gameMessage.fromJSON(json);
        return gameMessage;
    }
}
