import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';

import {Observable, of} from 'rxjs';
import {catchError} from 'rxjs/operators';
import {Recipe} from './recipe';

@Injectable({
  providedIn: 'root'
})
export class GenericService {
  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json'
    })
  };
  private backendUrl = 'http://127.0.0.1:8080/';

  constructor(private http: HttpClient) {
  }

  fetchRecipes(type: string, name: string): Observable<Recipe[]> {
    /* body of the method */
    return this.http.get<Recipe[]>(this.backendUrl + `showRecipes.php?type=${type}&name=${name}`)
      .pipe(catchError(this.handleError<Recipe[]>('fetchRecipes', []))
      );
  }

  deleteRecipe(recipeID: number): Observable<any> {
    return this.http.post(this.backendUrl + `deleteRecipeBackend.php`, {id: recipeID});
  }

  addRecipe(nameOf: string, typeOf: string, authorOf: string,
    ingredientsOf: string, instructionsOf: string, imageOf: string): Observable<any> {
    return this.http.post(this.backendUrl + `addRecipe.php`, {
      name: nameOf,
      author: authorOf,
      type: typeOf,
      ingredients: ingredientsOf,
      instructions: instructionsOf,
      image: imageOf
    });
  }

  updateRecipe(idOf: number, nameOf: string, typeOf: string, authorOf: string,
             ingredientsOf: string, instructionsOf: string, imageOf: string): Observable<any> {
    return this.http.post(this.backendUrl + `updateRecipeBackend.php`, {
      id: idOf,
      name: nameOf,
      author: authorOf,
      type: typeOf,
      ingredients: ingredientsOf,
      instructions: instructionsOf,
      image: imageOf
    });
  }

  private handleError<T>(operation = 'operation', result?: T): (error: any) => Observable<T> {
    return (error: any): Observable<T> => {
      console.error(error);
      return of(result as T);
    };
  }
}