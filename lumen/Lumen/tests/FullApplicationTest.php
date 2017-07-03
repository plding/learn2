<?php

use Illuminate\Http\Request;
use Lumen\Application;
use Symfony\Component\HttpFoundation\Request as SymfonyRequest;

class FullApplicationTest extends PHPUnit_Framework_TestCase
{
    public function testBasicRequest()
    {
        $app = new Application;

        $app->get('/', function() {
            return response('Hello World');
        });

        $response = $app->handle(Request::create('/', 'GET'));

        $this->assertEquals(200, $response->getStatusCode());
        $this->assertEquals('Hello World', $response->getContent());
    }
}
