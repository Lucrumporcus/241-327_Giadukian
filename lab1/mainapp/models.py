from django.db import models

class Book(models.Model):
    title = models.CharField(max_length=200) # название 
    author = models.CharField(max_length=200) # автор
    year = models.IntegerField() # год 
    price = models.DecimalField(max_digits=8, decimal_places=2) # цена
    is_available = models.BooleanField(default=True) # флаг наличия
    created_at = models.DateTimeField(auto_now_add=True) # дата выхода
    description = models.TextField(blank=True, null=True) # описание
    

