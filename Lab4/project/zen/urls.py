from django.conf.urls import url

from . import views

app_name = 'zen'

urlpatterns = [
    # ex: /zen/
    #url(r'^$', views.index, name='index'),
    # ex: /zen/#num/   where #num is a number
   # url(r'^(?P<post_id>[0-9]+)/$', views.detail, name='detail'),
]


