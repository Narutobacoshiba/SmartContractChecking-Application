import mysql.connector

db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '',
    database="Project"
)
mycursor = db.cursor()
mycursor.excute("""ALTER TABLE old_table_name RENAME SmartContract;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME Account;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME Contact;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME Functionss;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME LocalVariable;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME Argument;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME GlobalVariable;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME Context;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME SC_Context;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME Template;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME ProVul;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME SC_ProVul;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME History;""")
mycursor.excute("""ALTER TABLE old_table_name RENAME History_Type;""")