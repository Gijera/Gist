<?php

namespace App\Http\Controllers;
use Auth;
use Illuminate\Http\Request;
use App\Http\Requests;
use App\Http\Controllers\Controller;

class SessionsController extends Controller
{
	public function __construct(){
		$this->middleware('guest', ['only' => 'create','store']);
	}

    public function create(){
    	return view('sessions.create');
    }

    public function store(){
    	if (! Auth::attempt(['email' => request('email'), 'password' => request('password')])) {

    		return back()->withErrors([
    			'message' => 'Please check your credentials and try again'
    		]);
        }
        return redirect()->home();
    }

    public function destroy(){
        auth()->logout();
        return redirect()->home();
    }
}
