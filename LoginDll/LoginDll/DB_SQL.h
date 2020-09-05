//创建NDUser表
/*
Create Table NDUser
(
	id integer primary key autoincrement,
	coverageid integer,
	username varchar(64),
	password varchar(32)
);
*/

//插入测试数据 密码123456
/*
INSERT INTO NDUser (id, coverageid, username, password)
VALUES (NULL, 1, "508816", "e10adc3949ba59abbe56e057f20f883e");
*/

//查询语句
/*
select * from NDUser WHERE username='508816' AND password='e10adc3949ba59abbe56e057f20f883e';
*/
//

//创建UserProfile表
/*
Create Table CRLUserProfile
(
	id integer primary key autoincrement,
	userid integer,
	nickname varchar(64)
);
*/

//插入测试数据
/*
INSERT INTO NDUserProfile (id, userid, nickname)
VALUES (NULL, 28419641, "小牧");
*/

//创建NDCoverage表
/*
Create Table NDCoverage
(
	coverageid integer primary key autoincrement,
	coveragename varchar(64)
);
*/

//插入测试数据
/*
INSERT INTO NDCoverage (coverageid, coveragename)
VALUES (NULL, "nd");
*/

//查询
/*
select NDUser.id, NDUser.username, NDUserProfile.nickname, NDCoverage.coverageid, NDCoverage.coveragename from NDUser, NDUserProfile, NDCoverage where NDUser.id = %d and NDUser.coverageid = NDCoverage.coverageid and NDUser.id = NDUserProfile.userid;
*/