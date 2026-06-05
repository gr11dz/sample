from django.db import models


class User(models.Model):
    us_id = models.AutoField(primary_key= True)
    us_firstname = models.CharField(max_length= 255)
    us_lastname = models.CharField(max_length= 255)
    us_username = models.CharField(max_length= 255, unique= True)
    us_password = models.CharField(max_length= 255)

    class Meta:
        db_table = "user"

class Admin(models.Model):
    ad_id = models.AutoField(primary_key= True)
    us_id = models.ForeignKey(
                            User,
                            on_delete= models.CASCADE,
                            db_column="us_id",
                            )
    class Meta:
        db_table = "admin"

class Manager(models.Model):
    mg_id = models.AutoField(primary_key= True)
    us_id = models.ForeignKey(
                            User,
                            on_delete= models.CASCADE,
                            db_column="us_id",
                            )
    class Meta:
        db_table = "manager"


class Bank(models.Model):
    bk_id = models.AutoField(primary_key=True)
    bk_name = models.CharField(max_length=255, unique= True)
    bk_address = models.CharField(max_length= 255, null= True)
    class Meta:
        db_table = "bank"

class Degree(models.Model):
    dg_id = models.AutoField(primary_key= True)
    dg_name = models.CharField(max_length= 255, unique= True)
    class Meta:
        db_table = "degree"

class Department(models.Model):
    dp_id = models.AutoField(primary_key= True)
    dp_address = models.CharField(max_length= 255, null= True)
    dp_classAmount = models.PositiveIntegerField()
    dp_name = models.CharField(max_length= 255, unique= True)
    class Meta:
        db_table = "department"

class Student(models.Model):
    st_nationalid = models.AutoField(primary_key= True)
    st_firstname = models.CharField(max_length= 255)
    st_lastname = models.CharField(max_length= 255)
    st_age = models.PositiveSmallIntegerField()
    st_gender = models.BooleanField()
    class Meta:
        db_table = "student"

class Cheque(models.Model):
    cq_id = models.AutoField(primary_key= True)
    cq_number = models.IntegerField(null= True)
    cq_owner = models.CharField(max_length= 255)
    cq_bankname = models.ForeignKey(
        Bank,
        on_delete=models.SET_DEFAULT,
        default= 0,
        db_column="bk_id",
    )
    class Meta:
        db_table = "cheque"

class Payment(models.Model):
    pay_id = models.AutoField(primary_key= True)
    pay_amount = models.PositiveIntegerField(default=0)
    pay_method = models.CharField(max_length= 100)
    pay_date = models.DateTimeField(auto_now_add= True)
    cq_id = models.ForeignKey(
        Cheque,
        on_delete= models.CASCADE,
        db_column= "cq_id"
    )
    class Meta:
        db_table = "payment"

class Teacher(models.Model):
    th_nationalid = models.AutoField(primary_key= True)
    th_firstname = models.CharField(max_length= 255)
    th_lastname = models.CharField(max_length= 255)
    dg_id = models.ForeignKey(
        Degree,
        on_delete= models.SET_DEFAULT,
        default= 0,
        db_column= "dg_id"
    )
    class Meta:
        db_table = "teacher"

class Class(models.Model):
    cl_id = models.AutoField(primary_key= True)
    th_id = models.ForeignKey(
        Teacher,
        on_delete= models.SET_DEFAULT,
        default = 0,
        db_column= "th_id",
    )
    cl_fee = models.PositiveBigIntegerField()
    dp_id = models.ForeignKey(
        Department,
        on_delete= models.SET_DEFAULT,
        default= 0,
        db_column = "dp_id"
    )
    class Meta:
        db_table = "class"

class Register(models.Model):
    rg_id = models.AutoField(primary_key= True)
    st_id = models.ForeignKey(
        Student,
        on_delete= models.CASCADE,
        db_column= "st_id"
    )
    cl_id = models.ForeignKey(
        Class,
        on_delete= models.CASCADE,
        db_column = "cl_id"
    )
    pay_id = models.ForeignKey(
        Payment,
        on_delete= models.CASCADE,
        db_column = "pay_id"
    )
    rg_date = models.DateTimeField(auto_now_add= True)
    class Meta:
        db_table = "register"

class Inventory(models.Model):
    inv_id = models.AutoField(primary_key= True)
    inv_bookname = models.CharField(max_length= 255, unique= True)
    inv_bookamount = models.PositiveIntegerField()
    class Meta:
        db_table = "inventory"

class BookRequirements(models.Model):
    cl_id = models.ForeignKey(
        Class,
        on_delete = models.CASCADE,
        db_column = "cl_id"
    )
    inv_id = models.ForeignKey(
        Inventory,
        on_delete = models.CASCADE,
        db_column = "inv_id"
    )
    class Meta:
        db_table= "bookrequirements"