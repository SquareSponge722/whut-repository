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
import com.qst.dms.entity.MatchedTransport;
import com.qst.dms.entity.Transport;

public class TransportService {
	private static final String SAVE_FILE_NAME = "MatchedTransports.txt";

	// 物流数据采集
	public Transport inputTransport() {
		Transport trans = null;

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
			System.out.println("请输入地址：");
			// 接收键盘输入的字符串信息
			String address = scanner.next();
			// 数据状态是“采集”
			int type = DataBase.GATHER;

			// 提示用户输入登录用户名
			System.out.println("请输入货物经手人：");
			// 接收键盘输入的字符串信息
			String handler = scanner.next();
			// 提示用户输入主机IP
			System.out.println("请输入 收货人:");
			// 接收键盘输入的字符串信息
			String reciver = scanner.next();
			// 提示用于输入物流状态
			System.out.println("请输入物流状态：1发货中，2送货中，3已签收");
			// 接收物流状态
			int transportType = scanner.nextInt();
			// 创建物流信息对象
			trans = new Transport(id, nowDate, address, type, handler, reciver,
					transportType);
		} catch (Exception e) {
			System.out.println("采集的日志信息不合法");
		}
		// 返回物流对象
		return trans;
	}

	// 物流信息输出
	public void showTransport(Transport... transports) {
		for (Transport e : transports) {
			if (e != null) {
				System.out.println(e.toString());
			}
		}
	}

	// 匹配的物流信息输出，可变参数
	public void showMatchTransport(MatchedTransport... matchTrans) {
		for (MatchedTransport e : matchTrans) {
			if (e != null) {
				System.out.println(e.toString());
			}
		}
	}

	// 匹配的物流信息输出，参数是集合
	public void showMatchTransport(ArrayList<MatchedTransport> matchTrans) {
		for (MatchedTransport e : matchTrans) {
			if (e != null) {
				System.out.println(e.toString());
			}
		}
	}

	// 匹配物流信息保存，参数是集合
	public void saveMatchedTransport(ArrayList<MatchedTransport> matchTrans) {
		// 创建一个ObjectOutputStream对象输出流，并连接文件输出流
		// 以可追加的方式创建文件输出流，数据保存到MatchedTransports.txt文件中
		try (ObjectOutputStream obs = new ObjectOutputStream(
				new FileOutputStream(SAVE_FILE_NAME, true))) {
			// 循环保存对象数据
			for (MatchedTransport e : matchTrans) {
				if (e != null) {
					// 把对象写入到文件中
					obs.writeObject(e);
					obs.flush();
				}
			}
			// 文件末尾保存一个null对象，代表文件结束
			obs.writeObject(null);
			obs.flush();
			obs.close();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	// 读匹配物流信息保存，参数是集合
	public ArrayList<MatchedTransport> readMatchedTransport() {
		ArrayList<MatchedTransport> matchTrans = new ArrayList<>();
		// 创建一个ObjectInputStream对象输入流，并连接文件输入流，读MatchedTransports.txt文件中
		try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(
				SAVE_FILE_NAME))) {
			MatchedTransport matchTran;
			// 循环读文件中的对象
			/*
			while ((matchTran = (MatchedTransport) ois.readObject()) != null) {
				// 将对象添加到泛型集合中
				matchTrans.add(matchTran);
			}*/
			while (true) {
				try{
					matchTran = (MatchedTransport) ois.readObject();
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

	public void saveAndAppendTransport(ArrayList<MatchedTransport> matchedTransports) {
		try{
			AppendObjectOutputStream.file = new File(SAVE_FILE_NAME);
			AppendObjectOutputStream obs = new AppendObjectOutputStream(new FileOutputStream(SAVE_FILE_NAME,true));
			for (MatchedTransport e : matchedTransports) {
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

	public void saveMatchTransportToDB(ArrayList<MatchedTransport> matchedTrans) {
		DBUtil db = new DBUtil();
		try {
			db.getConnection();
			for (MatchedTransport matchedTransport: matchedTrans) {
				Transport send = matchedTransport.getSend();
				Transport trans = matchedTransport.getTrans();
				Transport receive = matchedTransport.getReceive();
				String sql = "INSERT INTO gather_transport(id,time,address,type,handler,reciver,transporttype) VALUES(?,?,?,?,?,?,?)";
				Object[] param = new Object[] {
					send.getId(),
					new Timestamp(send.getTime().getTime()),
					send.getAddress(),
					send.getType(),
					send.getHandler(),
					send.getReciver(),
					send.getTransportType()
				};
				db.executeUpdate(sql, param);
				param = new Object[] {
					trans.getId(),
					new Timestamp(trans.getTime().getTime()),
					trans.getAddress(),
					trans.getType(),
					trans.getHandler(),
					trans.getReciver(),
					trans.getTransportType()
				};
				db.executeUpdate(sql, param);
				param = new Object[] {
					receive.getId(),
					new Timestamp(receive.getTime().getTime()),
					receive.getAddress(),
					receive.getType(),
					receive.getHandler(),
					receive.getReciver(),
					receive.getTransportType()
				};
				db.executeUpdate(sql, param);

				sql = "INSERT INTO matched_transport(sendid,transid,receiveid) VALUES(?,?,?)";
				param = new Object[] {
					send.getId(),
					trans.getId(),
					receive.getId()
				};
				db.executeUpdate(sql, param);
			}
			db.closeAll();
		} catch(Exception e){
			e.printStackTrace();
		}
	}

	public ArrayList<MatchedTransport> readMatchedTransportFromDB() {
		ArrayList<MatchedTransport> matchedTransports = new ArrayList<MatchedTransport>();
		DBUtil db = new DBUtil();
		try {
			db.getConnection();
			String sql = "SELECT s.ID,s.TIME,s.ADDRESS,s.TYPE,s.HANDLER,s.RECIVER,s.TRANSPORTTYPE,"
				+ "t.ID,t.TIME,t.ADDRESS,t.TYPE,t.HANDLER,t.RECIVER,t.TRANSPORTTYPE,"
				+ "r.ID,r.TIME,r.ADDRESS,r.TYPE,r.HANDLER,r.RECIVER,r.TRANSPORTTYPE "
				+ "FROM MATCHED_TRANSPORT m,GATHER_TRANSPORT s,GATHER_TRANSPORT t,GATHER_TRANSPORT r "
				+ "WHERE m.SENDID=s.ID AND m.TRANSID=t.ID AND m.RECEIVEID=r.ID";
			ResultSet rs = db.executeQuery(sql, null);
			while (rs.next()) {
				Transport send = new Transport(rs.getInt(1), rs.getDate(2),
					rs.getString(3), rs.getInt(4), rs.getString(5),
					rs.getString(6), rs.getInt(7));
				Transport trans = new Transport(rs.getInt(8), rs.getDate(9),
					rs.getString(10), rs.getInt(11), rs.getString(12),
					rs.getString(13), rs.getInt(14));
				Transport receive = new Transport(rs.getInt(15), rs.getDate(16),
					rs.getString(17), rs.getInt(18), rs.getString(19),
					rs.getString(20), rs.getInt(21));
				MatchedTransport matchedTrans = new MatchedTransport(send,trans,receive);
				matchedTransports.add(matchedTrans);
			}
			db.closeAll();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return matchedTransports;
	}

	public ResultSet readTransResult() {
		DBUtil db = new DBUtil();
		ResultSet rs = null;
		try {
			Connection conn = db.getConnection();
			Statement st = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_UPDATABLE);
			String sql = "SELECT * from gather_transport";
			rs = st.executeQuery(sql);
			//db.closeAll();
		} catch (Exception e){
			e.printStackTrace();
		}
		return rs;
	}
}