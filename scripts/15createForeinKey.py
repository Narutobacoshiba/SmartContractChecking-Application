import mysql.connector

db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
mycursor.execute("""alter table Contact ADD CONSTRAINT fk_id1 FOREIGN KEY(aid)
references Account (id);""")
mycursor.execute("""alter table SmartContract ADD CONSTRAINT fk_aid2 FOREIGN KEY(aid)
references Account (id);""")
mycursor.execute("""alter table History ADD CONSTRAINT fk_scid3 FOREIGN KEY(scid)
references SmartContract (id);""")
mycursor.execute("""alter table History_Type ADD CONSTRAINT fk_htid4 FOREIGN KEY(htid)
references History (id);""")
mycursor.execute("""alter table ProVul ADD CONSTRAINT fk_tpid5 FOREIGN KEY(tpid)
references Template (id);""")
mycursor.execute("""alter table SC_ProVul ADD CONSTRAINT fk_scid6 FOREIGN KEY(scid)
references SmartContract (id);""")
mycursor.execute("""alter table SC_ProVul ADD CONSTRAINT fk_pvid7 FOREIGN KEY(pvid)
references ProVul (id);""")
mycursor.execute("""alter table SC_Context ADD CONSTRAINT fk_scid8 FOREIGN KEY(scid)
references SmartContract (id);""")
mycursor.execute("""alter table SC_Context ADD CONSTRAINT fk_ct9 FOREIGN KEY(ctid)
references Context (id);""")
mycursor.execute("""alter table Functionss ADD CONSTRAINT fk_scid10 FOREIGN KEY(scid)
references SmartContract (id);""")
mycursor.execute("""alter table GlobalVariable ADD CONSTRAINT fk_scid11 FOREIGN KEY(scid)
references SmartContract (id);""")
mycursor.execute("""alter table LocalVariable ADD CONSTRAINT fk_fid12 FOREIGN KEY(fid)
references Functionss (id);""")
mycursor.execute("""alter table Argument ADD CONSTRAINT fk_fid13 FOREIGN KEY(fid)
references Functionss (id);""")
