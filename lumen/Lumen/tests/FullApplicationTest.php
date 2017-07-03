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

    public function testRequestWithParameters()
    {
        $app = new Application;

        $app->get('/foo/{bar}/{baz}', function ($bar, $baz) {
            return response($bar.$baz);
        });

        $response = $app->handle(Request::create('/foo/1/2', 'GET'));

        $this->assertEquals(200, $response->getStatusCode());
        $this->assertEquals('12', $response->getContent());
    }

    public function testCallbackRouteWithDefaultParameter()
    {
        $app = new Application;
        $app->get('/foo-bar/{baz}', function ($baz = 'default-value') {
            return response($baz);
        });

        // $response = $app->handle(Request::create('/foo-bar', 'GET'));

        // $this->assertEquals(200, $response->getStatusCode());
        // $this->assertEquals('default-value', $response->getContent());

        $response = $app->handle(Request::create('/foo-bar/something', 'GET'));

        $this->assertEquals(200, $response->getStatusCode());
        $this->assertEquals('something', $response->getContent());
    }
}
