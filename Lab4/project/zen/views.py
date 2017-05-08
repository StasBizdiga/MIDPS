from django.http import HttpResponse,HttpResponseRedirect
from django.template import loader
from django.shortcuts import get_object_or_404, render
from django.urls import reverse
from django.views import generic
from .models import Post



def index(request):
    post_list = Post.objects.all()
    template = loader.get_template('zen/index.html')
    context = {
        'post_list': post_list,
    }
    return HttpResponse(template.render(context, request))
    
def detail(request, post_id):
    post = get_object_or_404(Post, pk=post_id)
    return render(request, 'zen/detail.html', {'post': post})

def home(request):
    return render(request, 'zen/home.html')
