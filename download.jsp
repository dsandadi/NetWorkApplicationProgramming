<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1" import ="java.io.*"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
<%
String fileName = "demo.txt";
String filePath = "G:\\";
response.setContentType("application/octet-stream");
response.setHeader("Content-Cisposition","attachment:filename=\""+fileName+"\"");
FileInputStream f = new FileInputStream(filePath+fileName); 
int i;
while((i = f.read())!= -1)
{
	out.write(i);
}
f.close();

%>
</body>
</html>