<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Carbon\Carbon;
use App\Http\Requests;
use App\Http\Controllers\Controller;
use App\Post;

class PostsController extends Controller
{
    public function __construct(){
        $this->middleware('auth', ['only' => ['create', 'store']]);
    }

    public function index(){
        $posts = Post::latest()
            ->filter([
                'month' => request('month'),
                'year' => request('year')
            ])
            ->get();

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
        auth()->user()->publish(
            new Post(request()->all())
        );

    	//跳转到主页
    	return redirect()->home();
    }
}
