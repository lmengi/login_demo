//����NDUser��
/*
Create Table NDUser
(
	id integer primary key autoincrement,
	coverageid integer,
	username varchar(64),
	password varchar(32)
);
*/

//����������� ����123456
/*
INSERT INTO NDUser (id, coverageid, username, password)
VALUES (NULL, 1, "508816", "e10adc3949ba59abbe56e057f20f883e");
*/

//��ѯ���
/*
select * from NDUser WHERE username='508816' AND password='e10adc3949ba59abbe56e057f20f883e';
*/
//

//����UserProfile��
/*
Create Table CRLUserProfile
(
	id integer primary key autoincrement,
	userid integer,
	nickname varchar(64)
);
*/

//�����������
/*
INSERT INTO NDUserProfile (id, userid, nickname)
VALUES (NULL, 28419641, "С��");
*/

//����NDCoverage��
/*
Create Table NDCoverage
(
	coverageid integer primary key autoincrement,
	coveragename varchar(64)
);
*/

//�����������
/*
INSERT INTO NDCoverage (coverageid, coveragename)
VALUES (NULL, "nd");
*/

//��ѯ
/*
select NDUser.id, NDUser.username, NDUserProfile.nickname, NDCoverage.coverageid, NDCoverage.coveragename from NDUser, NDUserProfile, NDCoverage where NDUser.id = %d and NDUser.coverageid = NDCoverage.coverageid and NDUser.id = NDUserProfile.userid;
*/