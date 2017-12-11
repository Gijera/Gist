<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

use App\Http\Requests;
use App\Http\Controllers\Controller;

class TagsController extends Controller
{
    public function index($id){
        $tag = \App\Tag::find($id);
        $posts = $tag->posts()->get();

        return view('posts.index', compact('posts'));
    }
}
