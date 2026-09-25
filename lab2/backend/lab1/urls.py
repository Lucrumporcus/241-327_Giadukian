from django.contrib import admin
from django.urls import path

from mainapp.views import BookViewSet


urlpatterns = [
    path('admin/', admin.site.urls),
    
    path('api/book/', BookViewSet.as_view({
        'get': 'list',
        'post': 'create',
    })),

    path('api/book/<pk>/', BookViewSet.as_view({
        'get': 'retrieve',
        'put': 'update',
        'patch': 'partial_update',
        'delete': 'destroy',
    })),
]
