package com.qst.dms.service;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

import com.qst.dms.db.DBUtil;
import com.qst.dms.entity.DataBase;
import com.qst.dms.entity.LogRec;
import com.qst.dms.entity.MatchedLogRec;
//日志业务类
public class LogRecService {
	private static final String SAVE_FILE_NAME = "matchedLogRecs.txt";
	private static final String INPUT_HINT = "请输入";
	private static final String ADDRESS = "地址";
	private static final String USER = "登录用户名";
	private static final String IP = "主机IP";

	// 日志数据采集
	public LogRec inputLog() {
		LogRec log = null;
		// 建立一个从键盘接收数据的扫描器
		@SuppressWarnings("all")
		Scanner scanner = new Scanner(System.in);
		try {
			// 提示用户输入ID标识
			System.out.println("请输入ID标识：");
			// 接收键盘输入的整数
			int id = scanner.nextInt();
			// 获取当前系统时间
			Date nowDate = new Date();
			// 提示用户输入地址
			System.out.println(INPUT_HINT + ADDRESS);
			// 接收键盘输入的字符串信息
			String address = scanner.next();
			// 数据状态是“采集”
			int type = DataBase.GATHER;
			// 提示用户输入登录用户名
			System.out.println(INPUT_HINT + USER);
			// 接收键盘输入的字符串信息
			String user = scanner.next();
			// 提示用户输入主机IP
			System.out.println(INPUT_HINT + IP);
			// 接收键盘输入的字符串信息
			String ip = scanner.next();
			// 提示用户输入登录状态、登出状态
			System.out.println("请输入登录状态:1是登录，0是登出");
			int logType = scanner.nextInt();
			// 创建日志对象
			log = new LogRec(id, nowDate, address, type, user, ip, logType);
		} catch (Exception e) {
			System.out.println("采集的日志信息不合法");
		}
		// 返回日志对象
		return log;
	}

	// 日志信息输出
	public void showLog(LogRec... logRecs) {
		for (LogRec e : logRecs) {
			if (e != null) {
				System.out.println(e.toString());
			}
		}
	}

	// 匹配日志信息输出，可变参数
	public void showMatchLog(MatchedLogRec... matchLogs) {
		for (MatchedLogRec e : matchLogs) {
			if (e != null) {
				System.out.println(e.toString());
			}
		}
	}

	// 匹配日志信息输出,参数是集合
	public void showMatchLog(ArrayList<MatchedLogRec> matchLogs) {
		for (MatchedLogRec e : matchLogs) {
			if (e != null) {
				System.out.println(e.toString());
			}
		}
	}

	// 覆盖保存
	public void saveMatchLog(ArrayList<MatchedLogRec> matchedLogRecs) {
		try (ObjectOutputStream obs = new ObjectOutputStream(
				new FileOutputStream(SAVE_FILE_NAME,false))) {
			for (MatchedLogRec e : matchedLogRecs) {
				if (e != null) {
					obs.writeObject(e);
					obs.flush();
				}
			}
			obs.writeObject(null);
			obs.flush();
			obs.close();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	public ArrayList<MatchedLogRec> readMatchLog(){
		ArrayList<MatchedLogRec> matchTrans = new ArrayList<>();
		try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(SAVE_FILE_NAME))) {
			MatchedLogRec matchTran;
			while (true) {
				try{
					matchTran = (MatchedLogRec) ois.readObject();
					matchTrans.add(matchTran);
				} catch (EOFException eofException){
					ois.close();
					break;
				}
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return matchTrans;
	}

	public void saveAndAppendMatchLog(ArrayList<MatchedLogRec> matchedLogRecs) {
		try{
			AppendObjectOutputStream.file = new File(SAVE_FILE_NAME);
			AppendObjectOutputStream obs = new AppendObjectOutputStream(new FileOutputStream(SAVE_FILE_NAME,true));
			for (MatchedLogRec e : matchedLogRecs) {
				if (e != null) {
					obs.writeObject(e);
					obs.flush();
				}
			}
			obs.writeObject(null);
			obs.flush();
			obs.close();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	public void saveMatchLogToDB(ArrayList<MatchedLogRec> matchedLogRecs) {
		DBUtil db = new DBUtil();
		try {
			db.getConnection();
			for (MatchedLogRec matchedLogRec: matchedLogRecs) {
				LogRec login = matchedLogRec.getLogin();
				LogRec logout = matchedLogRec.getLogout();
				String sql = "INSERT INTO gather_logrec(id,time,address,type,username,ip,logtype) VALUES(?,?,?,?,?,?,?)";
				Object[] param = new Object[] {
					login.getId(),
					new Timestamp(login.getTime().getTime()),
					login.getAddress(),
					login.getType(),
					login.getUser(),
					login.getIp(),
					login.getLogType()
				};
				db.executeUpdate(sql, param);
				param = new Object[] {
					logout.getId(),
					new Timestamp(logout.getTime().getTime()),
					logout.getAddress(),
					logout.getType(),
					logout.getUser(),
					logout.getIp(),
					logout.getLogType()
				};
				db.executeUpdate(sql, param);

				sql = "INSERT INTO matched_logrec(loginid,logoutid) VALUES(?,?)";
				param = new Object[] {
					login.getId(),
					logout.getId()
				};
				db.executeUpdate(sql, param);
			}
			db.closeAll();
		} catch (Exception e){
			e.printStackTrace();
		}
	}

	public ArrayList<MatchedLogRec> readMatchedLogFromDB() {
		ArrayList<MatchedLogRec> matchedLogRecs = new ArrayList<MatchedLogRec>();
		DBUtil db = new DBUtil();
		try {
			db.getConnection();
			String sql = "SELECT s.ID,s.TIME,s.ADDRESS,s.TYPE,s.USERNAME,s.IP,s.LOGTYPE,"
				+ "t.ID,t.TIME,t.ADDRESS,t.TYPE,t.USERNAME,t.IP,t.LOGTYPE "
				+ "FROM MATCHED_LOGREC m,GATHER_LOGREC s,GATHER_LOGREC t "
				+ "WHERE m.LOGINID=s.ID AND m.LOGOUTID=t.ID";
			ResultSet rs = db.executeQuery(sql, null);
			while (rs.next()) {
				LogRec login = new LogRec(rs.getInt(1),rs.getDate(2),
					rs.getString(3),rs.getInt(4),rs.getString(5),
					rs.getString(6),rs.getInt(7));
				LogRec logout = new LogRec(rs.getInt(8),rs.getDate(9),
				rs.getString(10),rs.getInt(11),rs.getString(12),
				rs.getString(13),rs.getInt(14));
				MatchedLogRec matchedLogRec = new MatchedLogRec(login,logout);
				matchedLogRecs.add(matchedLogRec);
			}
			db.closeAll();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return matchedLogRecs;
	}

	public ResultSet readLogResult() {
		DBUtil db = new DBUtil();
		ResultSet rs = null;
		try {
			Connection conn = db.getConnection();
			Statement st = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_UPDATABLE);
			String sql = "SELECT * from gather_logrec";
			rs = st.executeQuery(sql);
			//db.closeAll();
		} catch (Exception e){
			e.printStackTrace();
		}
		return rs;
	}
}
