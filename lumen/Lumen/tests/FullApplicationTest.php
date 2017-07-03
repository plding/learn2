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

    public function testBasicSymfonyRequest()
    {
        $app = new Application;

        $app->get('/', function () {
            return response('Hello World');
        });

        $response = $app->handle(SymfonyRequest::create('/', 'GET'));
        $this->assertEquals(200, $response->getStatusCode());
    }

    public function testAddRouteMultipleMethodRequest()
    {
        $app = new Application;

        $app->addRoute(['GET', 'POST'], '/', function () {
            return response('Hello World');
        });

        $response = $app->handle(Request::create('/', 'GET'));

        $this->assertEquals(200, $response->getStatusCode());
        $this->assertEquals('Hello World', $response->getContent());

        $response = $app->handle(Request::create('/', 'POST'));

        $this->assertEquals(200, $response->getStatusCode());
        $this->assertEquals('Hello World', $response->getContent());
    }
}
