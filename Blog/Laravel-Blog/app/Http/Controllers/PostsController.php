<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

use App\Http\Requests;
use App\Http\Controllers\Controller;
use App\Post;

class PostsController extends Controller
{
    public function index(){
    	$posts = Post::latest()->get();

        return view('posts.index', compact('posts'));
    }

    public function show(Post $post){
    	return view('posts.show',compact('post'));
    }

    public function create(){
    	return view('posts.create');
    }

    public function store(){
    	//验证表单
    	$this->validate(request(),[
    		'title' => 'required|min:2',
    		'body' => 'required'
    	]);

    	//创建并保存Post对象
    	Post::create([
    		'title' => request('title'),
    		'body' => request('body')
    	]);

    	//跳转到主页
    	return redirect('/');
    }
}
