from datetime import datetime,timedelta
s="2024-01-01 10:25:25"
s_dt=datetime.strptime(s,"%Y-%m-%d %H:%M:%S")
s_dt=s_dt+timedelta(minutes=1000)
print(s_dt.strftime("%Y-%m-%d %H:%M:%S"))