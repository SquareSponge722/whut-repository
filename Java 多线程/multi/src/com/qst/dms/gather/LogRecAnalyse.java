package com.qst.dms.gather;

import java.util.ArrayList;
import java.util.Iterator;

import com.qst.dms.entity.DataBase;
import com.qst.dms.entity.LogRec;
import com.qst.dms.entity.MatchedLogRec;
import com.qst.dms.exception.DataAnalyseException;

//日志分析类，继承DataFilter抽象类，实现数据分析接口
public class LogRecAnalyse extends DataFilter implements IDataAnalyse {
	private static final String DATA_UNMATCHED_HINT = "存在不匹配数据！";
	// “登录”集合
	private ArrayList<LogRec> logIns = new ArrayList<>();
	// “登出”集合
	private ArrayList<LogRec> logOuts = new ArrayList<>();

	// 构造方法
	public LogRecAnalyse() {
	}

	public LogRecAnalyse(ArrayList<LogRec> logRecs) {
		super(logRecs);
	}

	// 实现DataFilter抽象类中的过滤抽象方法
	public void doFilter() {
		// 获取数据集合
		ArrayList<LogRec> logs = (ArrayList<LogRec>) this.getDatas();

		// 遍历，对日志数据进行过滤，根据日志登录状态分别放在不同的数组中
		logs.forEach(it -> {
			if(it.getLogType() == LogRec.LOG_IN){ // 添加到“登录”日志集合中
				logIns.add(it);
			}else if(it.getLogType() == LogRec.LOG_OUT){ // 添加到“登出”日志集合中
				logOuts.add(it);
			}
		});	
	}
	// 实现IDataAnalyse接口中数据分析方法
	public ArrayList<MatchedLogRec> matchData() {
		// 创建日志匹配集合
		ArrayList<MatchedLogRec> matchLogs = new ArrayList<>();

		// 数据匹配分析
		
		//try 
				// 没找到匹配的数据,抛出DataAnalyseException异常
		//catch (DataAnalyseException e) {
			//e.printStackTrace();
		try {
			for(Iterator<LogRec> iterator = logIns.iterator();iterator.hasNext();){
				LogRec logIn = iterator.next();
				boolean matched = false;
				for(Iterator<LogRec> iterator2 = logOuts.iterator();iterator2.hasNext();){
					LogRec logOut = iterator2.next();
					if(logIn.getIp().equals(logOut.getIp()) && logIn.getUser().equals(logOut.getUser())){
						if(logIn.getTime().after(logOut.getTime())) throw new DataAnalyseException(DATA_UNMATCHED_HINT);
						matchLogs.add(new MatchedLogRec(logIn,logOut));
						matched = true;
						iterator2.remove();
						break;
					}
				}
				if(matched){
					iterator.remove();
				}else{
					throw new DataAnalyseException(DATA_UNMATCHED_HINT);
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

		return matchLogs;
	}
}