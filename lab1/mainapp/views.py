from django.shortcuts import render

from django.conf import settings

import rest_framework
from rest_framework import viewsets

from .models import Book
from .serializers import BookSerializer

class BookViewSet(viewsets.ModelViewSet):
    queryset = Book.objects.all()
    serializer_class = BookSerializer